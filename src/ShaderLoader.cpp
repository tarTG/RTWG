/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShaderLoader.cpp
 * Author: tartg
 * 
 * Created on 18. Oktober 2016, 12:39
 */

#include <sstream>

#include "ShaderLoader.h"

GLuint ShaderLoader::generateProgram(const std::string& pathName) 
{
    GLuint program = glCreateProgram(); //create a new program

    //try to load and attach shader stages
    ShaderLoader::attachShader(program,pathName + ".vs.glsl",GL_VERTEX_SHADER);

    ShaderLoader::attachShader(program, pathName + ".tcs.glsl", GL_TESS_CONTROL_SHADER);

    ShaderLoader::attachShader(program, pathName + ".tes.glsl",GL_TESS_EVALUATION_SHADER);

    ShaderLoader::attachShader(program, pathName + ".gs.glsl", GL_GEOMETRY_SHADER);
    
    ShaderLoader::attachShader(program,pathName + ".fs.glsl",GL_FRAGMENT_SHADER);
    
    ShaderLoader::attachShader(program, pathName + ".cs.glsl",GL_COMPUTE_SHADER);
    
    //link program
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status); //get program status

    if (!status) //if there is an error
    {
        //print error to console
        char buffer[4096];
        glGetProgramInfoLog(program, 4096, NULL, buffer);
        std::stringstream s;        
        s << buffer;
        std::cout  << "Error Program link in "  << s.str()<< std::endl;
        glDeleteProgram(program);
        return 0;
    }
    return program; //return ID
}

void ShaderLoader::attachShader(GLuint& program, std::string filename, GLenum shader_type) 
{
    GLuint ret =  loadShaders( filename,shader_type); //load shader 
    if(ret != 0) //if shader exists
        glAttachShader(program, ret); //attach to program
}



GLuint ShaderLoader::loadShaders(const std::string filename, GLenum shader_type)
{
    GLuint result = 0;
    FILE * fp;
    size_t filesize;
    char * data;
    
    
    fp = fopen(filename.c_str(), "rb"); //read from file
    
    if (!fp) //if not available
        return result; //return 0
    
    //get filesize
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET); //reset file pointer

    data =  new char [filesize + 1];    //create buffer
    
    if (!data) //if this fails
        return result; //return 0 

    auto index =  fread(data, 1, filesize, fp); //read data from file to buffer
    data[index] = 0;
    fclose(fp); //close file

    result = glCreateShader(shader_type); //create shader

    if (!result) //if shader is not created
        return result; //return 0

    glShaderSource(result, 1, &data, NULL); //add shader source

    //compie shader
    glCompileShader(result);

    GLint status = 0;
    glGetShaderiv(result, GL_COMPILE_STATUS, &status); //get shader status

    if (!status) //if there is an error, print to console
    {
        char buffer[4096] ;
        glGetShaderInfoLog(result, 4096, NULL, buffer);
        std::stringstream s;
        s <<"Fail Shader " << filename  << " in " << buffer;
        std::cout << s.str() << std::endl;
        glDeleteShader(result);
    }
    
    delete[] data; //delete buffer
    
    return result; //return shader ID

}