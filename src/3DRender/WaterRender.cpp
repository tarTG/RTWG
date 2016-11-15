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

WaterRender::WaterRender(std::shared_ptr<plane> terrainPlain,const glm::ivec2& textureDimension)
:terrainPlain(terrainPlain), textureDimension(textureDimension)
{

}


void WaterRender::init(const std::string& shaderPath, const std::string& normalTexturePath, TwBar* Bar3d)
{
    glBindVertexArray(terrainPlain->getVao_plane());

    waterNormals =   TextureLoader::load2DTexture(normalTexturePath,GL_RGB, GL_UNSIGNED_BYTE,
                                                        IL_RGB,IL_UNSIGNED_BYTE);

    waterProgram = ShaderLoader::generateProgram(shaderPath);
    
    waterFlows = std::make_unique<RendToTex>(std::string(SHADER_PATH ) + "display/3D/waterFlow",textureDimension.x,textureDimension.y,GL_RGB,GL_NEAREST);
    waterFlows->setUniforms({{3.0,"WaterSpeed"}});
    waterFlows->generateParameterBar(Bar3d ,"",{"min=0.0 max = 10.0 step = 0.1"});

    glBindVertexArray(0);
}


void WaterRender::render(std::shared_ptr<Camera> camera, std::shared_ptr<Shadows> shadows,std::shared_ptr<Light> light, const float time , const float heightFactor)
{
    
    glViewport(0.0,0.0,textureDimension.x,textureDimension.y);
   glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_2D, waterFlows->getSourceTexture());
    waterFlows->update();
    glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_2D, 0);
    camera->loadViewPort();
    
    
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

        
    glUniform1f(glGetUniformLocation(waterProgram, "waterSpeed"),5.0);
     
   glUniform1f(glGetUniformLocation(waterProgram, "heightFactor"),heightFactor);
 
   glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, shadows->getDepthTexture());

    glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_2D, waterNormals);

        glActiveTexture(GL_TEXTURE11);
        glBindTexture(GL_TEXTURE_2D, waterFlows->getDestinationTexture());


    glDrawElements(GL_PATCHES,terrainPlain->getPlaneVertices(), GL_UNSIGNED_INT, 0);
    glUseProgram(0);
        
        glDisable(GL_BLEND);

    glDepthMask(GL_TRUE);
    glBindVertexArray(0);
   glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glActiveTexture(GL_TEXTURE11);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    waterFlows->swapTexture();

}

void WaterRender::exit()
{

}



