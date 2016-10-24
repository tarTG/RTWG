/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShaderLoader.h
 * Author: tartg
 *
 * Created on 18. Oktober 2016, 12:39
 */

#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include "../3rdParty/GL3W/gl3w.h"
#include "../3rdParty/GL3W/glcorearb.h"
#include <string>
#include <iostream>

class ShaderLoader {
public:

    /**
     * generate a new openGL shader program
     * @param pathName - path and name of the shaders
     * @return Id of the shader program
     */
     static GLuint generateProgram(const std::string& pathName);
private:
    
    /**
     * load Shaders for file
     * @param filename - name of the shader file
     * @param shader_type - type of the shader file
     * @return ID of the shader pipeline step
     */
    static GLuint loadShaders(const std::string filename, GLenum shader_type);
    
    /**
     * Attach shader to program
     * @param program - program ID
     * @param filename - filename of the shader 
     * @param shader_type - typ of the shader
     */
    static void attachShader(GLuint& program, std::string filename,GLenum shader_type);



 

};

#endif /* SHADERLOADER_H */

