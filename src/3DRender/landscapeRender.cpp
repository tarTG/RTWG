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

landscapeRender::landscapeRender(std::shared_ptr<plane> terrainPlain ) 
    :terrainPlain(terrainPlain)
{
}

void landscapeRender::init(const std::string& shaderPath)
{
    displayProgram = ShaderLoader::generateProgram(shaderPath);
}

void landscapeRender::render(std::shared_ptr<Camera> camera, std::shared_ptr<Shadows> shadow,std::shared_ptr<Light> light,const uint32_t currentDisplay, float heightFactor)
{
   glUseProgram(displayProgram);

    glUniformMatrix4fv(glGetUniformLocation(displayProgram, "model_matrix"),1,GL_FALSE,glm::value_ptr( terrainPlain->getModel_matrix()  ));
    glUniformMatrix4fv(glGetUniformLocation(displayProgram, "mv_matrix"),1,GL_FALSE,glm::value_ptr(  terrainPlain->getModel_matrix()  * camera->getView() ));
    glUniformMatrix4fv(glGetUniformLocation(displayProgram, "proj_matrix"),1,GL_FALSE,glm::value_ptr(camera->getProjection()    ));   
    glUniform3fv(glGetUniformLocation(displayProgram, "light_pos"),1,glm::value_ptr(light->getCurrentData().Position ));
    glUniform3fv(glGetUniformLocation(displayProgram, "light_color"),1,glm::value_ptr(light->getCurrentData().Color ));
    
    glUniform1ui(glGetUniformLocation(displayProgram, "currentSelection"),currentDisplay);

   glUniform2iv(glGetUniformLocation(displayProgram, "dimensions"),1,glm::value_ptr(terrainPlain->getPlaneDimension()));
    glUniformMatrix4fv(glGetUniformLocation(displayProgram,"shadowMVP"), 1, GL_FALSE, glm::value_ptr(shadow->getBiasedDepthMVP()));

   glUniform1f(glGetUniformLocation(displayProgram, "heightFactor"),heightFactor);

   glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, shadow->getDepthTexture());


    glDrawElements(GL_PATCHES,terrainPlain->getPlaneVertices(), GL_UNSIGNED_INT, 0);
    glUseProgram(0);

   glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void landscapeRender::exit()
{
    glDeleteProgram(displayProgram);
}

