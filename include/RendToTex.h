/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RendToTex.h
 * Author: tg
 *
 * Created on 15. Februar 2016, 11:02
 */

#ifndef RENDTOTEX_H
#define RENDTOTEX_H


#include "GL3W/gl3w.h"
#include <array>
#include <string>
#include <vector>

#include <AntTweakBar.h>
#include "ShaderLoader.h"
#include "TextureLoader.h"

class RendToTex 
{
public:
    RendToTex(unsigned int _sourceBuffer, unsigned int _destinationBuffer,const std::string& shaderPath,   unsigned int textureWidth, unsigned int textureHeight, const GLuint colorFormat,const GLuint interpolation = GL_LINEAR);
    
    void setUniforms(const std::vector<std::pair<float,std::string>>& uniforms);
    
    
    void exit();
     
    void update();
    
    GLuint getSourceTexture();
    
    GLuint getDestinationTexture();
    
    void generateParameterBar(TwBar *bar,const std::string& subSectionName,const std::vector<std::string> options);
    
    void generateActivationBar(TwBar *bar,const std::string& subSectionName);
       
    
    void swapTexture();
    
    void setTexture(const float* data);
    
    void setParameterValue(const std::string& parameter, float value);
    
    float getParameterValue(const std::string& parameter);
    
    float* getTexture();

        void reset();
        
    ILuint prepareExport();
    
private:
    std::array<GLuint,2> textureBuffer;
    std::vector<std::pair<float,std::string>> v_Uniforms;
    std::array<GLuint, 2> fboBuffer;
    unsigned int sourceBuffer;
    unsigned int destinationBuffer;    
    unsigned int textureWidth;
    unsigned int textureHeight;    
    GLuint colorFormat;
    GLuint shaderID;
    GLuint pixelBuffer;
    GLboolean enable;
    


    
};

#endif /* RENDTOTEX_H */

