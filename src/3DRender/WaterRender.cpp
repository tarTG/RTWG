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


#include "WaterRender.h"

WaterRender::WaterRender(const GLuint vao_plane, const float gridVertices, const glm::ivec2& gridDimensions)
:vao_plane(vao_plane),  gridVertices(gridVertices) ,gridDimensions(gridDimensions){

}


void WaterRender::init(const std::string& shaderPath, const std::string& normalTexturePath)
{

    glBindVertexArray(vao_plane);

    waterNormals =   TextureLoader::load2DTexture(normalTexturePath,GL_RGB, GL_UNSIGNED_BYTE,
                                                        IL_RGB,IL_UNSIGNED_BYTE);

    waterProgram = ShaderLoader::generateProgram(shaderPath);

    glBindVertexArray(0);
}


void WaterRender::render()
{
    /*
    auto transform = (TransformProperty*)GameObjectFactory::getInstance().getGameObject(13)->getProperty((int)IObjectProperty::properties::TransformProperty);
    auto camera = renderingHandler::getInstance()->getCamera();

        
     glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);        
   glUseProgram(waterProgram);

    glBindVertexArray(vao_plane);

   glUniform2iv(glGetUniformLocation(waterProgram, "dimensions"),1,glm::value_ptr(gridDimensions));

    glUniformMatrix4fv(glGetUniformLocation(waterProgram,"shadowMVP"), 1, GL_FALSE,
                       glm::value_ptr(biasMatrix*depthMVP));
        glUniformMatrix4fv(glGetUniformLocation(waterProgram, "model_matrix"),1,GL_FALSE,glm::value_ptr( transform->getMV()  ));
        glUniformMatrix4fv(glGetUniformLocation(waterProgram, "mv_matrix"),1,GL_FALSE,glm::value_ptr( transform->getMV()  * camera->getView() ));
        glUniformMatrix4fv(glGetUniformLocation(waterProgram, "proj_matrix"),1,GL_FALSE,glm::value_ptr(camera->getProjection()    ));   
        glUniform3fv(glGetUniformLocation(waterProgram, "light_pos"),1,glm::value_ptr(LightManager::getInstance().getAllLights()[0].Position ));
        glUniform3fv(glGetUniformLocation(waterProgram, "light_color"),1,glm::value_ptr(LightManager::getInstance().getAllLights()[0].Color ));

        
    glUniform1f(glGetUniformLocation(waterProgram, "waterSpeed"),waterSpeed);
     
   glUniform1f(glGetUniformLocation(waterProgram, "heightFactor"),heightFactor);
   glUniform1f(glGetUniformLocation(waterProgram, "timeFactor"),timeFactor);

   glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, depthTexture);

    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, waterNormals);



    glDrawElements(GL_PATCHES,drawSize, GL_UNSIGNED_INT, 0);
    glUseProgram(0);
        
        glDisable(GL_BLEND);

    glDepthMask(GL_TRUE);
    glBindVertexArray(0);
   glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, 0);
       glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE11);
    glBindTexture(GL_TEXTURE_2D, 0);*/
}

void WaterRender::exit()
{

}



