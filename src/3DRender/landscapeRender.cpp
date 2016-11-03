/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   landscapeRender.cpp
 * Author: tg
 * 
 * Created on 2. November 2016, 11:50
 */

#include "landscapeRender.h"

landscapeRender::landscapeRender(GLuint vao_plane, uint32_t drawSize, const glm::ivec2 gridDimensions ) 
    :vao_plane(vao_plane),drawSize(drawSize), gridDimensions(gridDimensions)
{
}

void landscapeRender::init(const std::string& shaderPath)
{
    displayProgram = ShaderLoader::generateProgram(shaderPath);
}

void landscapeRender::render(const uint32_t currentDisplay,const glm::mat4 depthMVP,GLuint depthTexture, float heightFactor)
{
   glUseProgram(displayProgram);

    glBindVertexArray(vao_plane);
    glUniform1ui(glGetUniformLocation(displayProgram, "currentSelection"),currentDisplay);

   glUniform2iv(glGetUniformLocation(displayProgram, "dimensions"),1,glm::value_ptr(gridDimensions));
    glUniformMatrix4fv(glGetUniformLocation(displayProgram,"shadowMVP"), 1, GL_FALSE,
                       glm::value_ptr(depthMVP));

   glUniform1f(glGetUniformLocation(displayProgram, "heightFactor"),heightFactor);

   glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, depthTexture);


    glDrawElements(GL_PATCHES,drawSize, GL_UNSIGNED_INT, 0);
    glUseProgram(0);
    glBindVertexArray(0);
   glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void landscapeRender::exit()
{
    glDeleteProgram(displayProgram);
}

