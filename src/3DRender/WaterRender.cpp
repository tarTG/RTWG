/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WaterRender.cpp
 * Author: tg
 * 
 * Created on 2. November 2016, 11:49
 */


#include <memory>

#include "WaterRender.h"
#include "plane.h"

WaterRender::WaterRender(std::shared_ptr<plane> terrainPlain)
:terrainPlain(terrainPlain)
{

}


void WaterRender::init(const std::string& shaderPath, const std::string& normalTexturePath)
{

    glBindVertexArray(terrainPlain->getVao_plane());

    waterNormals =   TextureLoader::load2DTexture(normalTexturePath,GL_RGB, GL_UNSIGNED_BYTE,
                                                        IL_RGB,IL_UNSIGNED_BYTE);

    waterProgram = ShaderLoader::generateProgram(shaderPath);


    glBindVertexArray(0);
}


void WaterRender::render(std::shared_ptr<Camera> camera, std::shared_ptr<Shadows> shadows,std::shared_ptr<Light> light, const float time , const float heightFactor)
{
    
    auto transform = terrainPlain->getModel_matrix();
        
     glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);        
   glUseProgram(waterProgram);


   glUniform2iv(glGetUniformLocation(waterProgram, "dimensions"),1,glm::value_ptr(terrainPlain->getPlaneDimension()));

    glUniformMatrix4fv(glGetUniformLocation(waterProgram,"shadowMVP"), 1, GL_FALSE,
                       glm::value_ptr(shadows->getBiasedDepthMVP()));
        glUniformMatrix4fv(glGetUniformLocation(waterProgram, "model_matrix"),1,GL_FALSE,glm::value_ptr( transform ));
        glUniformMatrix4fv(glGetUniformLocation(waterProgram, "mv_matrix"),1,GL_FALSE,glm::value_ptr( transform  * camera->getView() ));
        glUniformMatrix4fv(glGetUniformLocation(waterProgram, "proj_matrix"),1,GL_FALSE,glm::value_ptr(camera->getProjection()    ));   
        glUniform3fv(glGetUniformLocation(waterProgram, "light_pos"),1,glm::value_ptr(light->getCurrentData().Position ));
        glUniform3fv(glGetUniformLocation(waterProgram, "light_color"),1,glm::value_ptr(light->getCurrentData().Color ));

        
    glUniform1f(glGetUniformLocation(waterProgram, "waterSpeed"),5);
     
   glUniform1f(glGetUniformLocation(waterProgram, "heightFactor"),heightFactor);
   movementTime += time;
   glUniform1f(glGetUniformLocation(waterProgram, "timeFactor"),time);

   glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, shadows->getDepthTexture());

    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, waterNormals);



    glDrawElements(GL_PATCHES,terrainPlain->getPlaneVertices(), GL_UNSIGNED_INT, 0);
    glUseProgram(0);
        
        glDisable(GL_BLEND);

    glDepthMask(GL_TRUE);
    glBindVertexArray(0);
   glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, 0);

        glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void WaterRender::exit()
{

}



