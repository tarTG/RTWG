/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   display2D.cpp
 * Author: tg
 * 
 * Created on 27. Oktober 2016, 10:55
 */


#include <memory>

#include "display2D.h"

display2D::display2D(const std::string& shaderPath)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    displayProgram = ShaderLoader::generateProgram(std::string(SHADER_PATH ) +shaderPath);
    glBindVertexArray(0);
}
void display2D::render(std::array<GLint,2> windowDimensions, unsigned int currentSelection, GLuint textureID)
{
    glViewport(0,0,windowDimensions.at(0),windowDimensions.at(1));
        glBindVertexArray(vao);

     glUseProgram(displayProgram);
     
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D,textureID);
     
    glUniform1ui(glGetUniformLocation(displayProgram, "currentSelection"),currentSelection);
    glUniform2iv(glGetUniformLocation(displayProgram, "WindowDimension"),1,windowDimensions.data());


    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
     glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
        glBindVertexArray(0);
}

void display2D::exit()
{
    glDeleteProgram(displayProgram);
    glDeleteVertexArrays(1,&vao);
}

