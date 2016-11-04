/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Shadows.cpp
 * Author: tg
 * 
 * Created on 2. November 2016, 11:51
 */


#include "Shadows.h"


Shadows::Shadows(std::shared_ptr<plane> terrainPlain )
    :terrainPlain(terrainPlain)
{
}

void Shadows::init(const std::string& shaderPath)
{
    glBindVertexArray(terrainPlain->getVao_plane());

    shaderID = ShaderLoader::generateProgram(shaderPath);
    glGenFramebuffers(1, &depthFBO);
    glBindFramebuffer(GL_FRAMEBUFFER,depthFBO);
    
    glGenTextures(1,&depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT, 1024,1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT,nullptr); 
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //setup Opengl Texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE); //setup Opengl Texture
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL); //setup Opengl Texture
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,0x884E);        
    
      glFramebufferTexture(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,depthTexture,0);
        glDrawBuffer(GL_NONE);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Shadows::render(const float heightFactor,const glm::vec3& lightPosition)
{
    glBindFramebuffer(GL_FRAMEBUFFER,depthFBO);
     glCullFace(GL_FRONT);

    glViewport(0,0,1024, 1024);

    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderID);



    glUniform2iv(glGetUniformLocation(shaderID, "dimensions"),1,glm::value_ptr(terrainPlain->getPlaneDimension()));
    glUniform1f(glGetUniformLocation(shaderID, "heightFactor"),heightFactor);
    
    
     depthMVP = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, -100.0f, 20000.0f)
                        * glm::lookAt( lightPosition*glm::vec3(10),glm::vec3(terrainPlain->getPlaneDimension().x/2.0,5.0,terrainPlain->getPlaneDimension().y/2.0), glm::vec3(0,1,0))
                      * glm::mat4(1.0) ;
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"depthMVP"), 1, GL_FALSE,
                       glm::value_ptr(depthMVP));
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model_matrix"),1,GL_FALSE,glm::value_ptr( terrainPlain->getModel_matrix()));

    glDrawElements(GL_PATCHES,terrainPlain->getPlaneVertices(), GL_UNSIGNED_INT, 0);
    glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glClear( GL_DEPTH_BUFFER_BIT);


    glCullFace(GL_BACK);
}

const glm::mat4 Shadows::getBiasedDepthMVP()
{
    glm::mat4 biasMatrix(0.5,0.0,0.0,0.0,
                0.0,0.5,0.0,0.0,
                0.0,0.0,0.5,0.0,
                 0.5,0.5,0.5,1.0);
    return biasMatrix*depthMVP;
}

GLuint Shadows::getDepthTexture() const
{
    return depthTexture;
}


void Shadows::exit()
{
    glDeleteFramebuffers(1,&depthFBO);
    glDeleteProgram(shaderID);
    glDeleteTextures(1,&depthTexture);
}
