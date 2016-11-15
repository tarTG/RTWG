/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RendToTex.cpp
 * Author: tg
 * 
 * Created on 15. Februar 2016, 11:02
 */

#include <vector>
#include <deque>
#include "cstring"

#include "RendToTex.h"


RendToTex::RendToTex(const std::string& shaderPath, unsigned int textureWidth, unsigned int textureHeight, const GLuint colorFormat, const GLuint interpolation)
            : textureWidth(textureWidth), textureHeight(textureHeight), colorFormat(colorFormat), enable(true)
{
    shaderID = ShaderLoader::generateProgram(shaderPath);
    glGenFramebuffers(2,fboBuffer.data());
    glGenBuffers(1,&pixelBuffer);
    
    glBindFramebuffer(GL_FRAMEBUFFER,fboBuffer.at(sourceBuffer));

    textureBuffer.at(sourceBuffer) = TextureLoader::loadEmpty2DTexture(textureWidth, textureHeight,colorFormat,GL_FLOAT ,interpolation);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureBuffer.at(sourceBuffer), 0);
    glBindBuffer(GL_FRAMEBUFFER,0);

    glBindFramebuffer(GL_FRAMEBUFFER,fboBuffer.at(destinationBuffer));
    
    textureBuffer.at(destinationBuffer) = TextureLoader::loadEmpty2DTexture(textureWidth, textureHeight,colorFormat,GL_FLOAT,interpolation);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,  textureBuffer.at(destinationBuffer), 0);
    
    glBindBuffer(GL_FRAMEBUFFER,0);
    glBindTexture(GL_TEXTURE_2D, 0);  
    reset();    
}

void RendToTex::setUniforms(const std::vector<std::pair<float, std::string> >& uniforms)
{
    v_Uniforms = std::move(uniforms);
}



void RendToTex::update()
{
    if(!enable)
        return;
    glUseProgram(shaderID);
    
    glBindFramebuffer(GL_FRAMEBUFFER,fboBuffer.at(destinationBuffer));
    static const GLenum draw_buffers[] = {GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1 ,draw_buffers);
      
    
    for(const auto& uni : v_Uniforms)
    {
        glUniform1f(glGetUniformLocation(shaderID, uni.second.c_str()),uni.first);
    }

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);    
      
    glUseProgram(0);
}

void RendToTex::generateParameterBar(TwBar* bar, const std::string& subSectionName, const std::vector<std::string> options)
{
    for(auto& uni : v_Uniforms)
    {
        std::string s= "group='" + subSectionName + "' " + options.at(std::distance(v_Uniforms.data(),&uni)).c_str();
        TwAddVarRW(bar,uni.second.c_str(),TW_TYPE_FLOAT,&uni.first,s.c_str() );
    }
}

void RendToTex::generateActivationBar(TwBar* bar, const std::string& subSectionName)
{
    std::string s= "group='" + subSectionName + "' ";
    std::string name_1 = "Enable " + subSectionName;
    TwAddVarRW(bar,name_1.c_str(),TW_TYPE_BOOLCPP,&enable,s.c_str() );
    std::string name_2 = "Reset " + subSectionName;
    TwAddButton(bar,name_2.c_str(),[](void* clientData){static_cast<RendToTex*>(clientData)->reset();},this,s.c_str());
}


GLuint RendToTex::getSourceTexture()
{
    return textureBuffer.at(sourceBuffer);
}

GLuint RendToTex::getDestinationTexture()
{
    return textureBuffer.at(destinationBuffer);
}


void RendToTex::swapTexture()
{
    if(enable)
        std::swap(sourceBuffer,destinationBuffer);
}

float* RendToTex::getTexture()
{
    
    float* tmp;
     if(colorFormat == GL_RED)
    {
         tmp= new float[textureHeight* textureWidth ];
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, getSourceTexture());  

        glGetTexImage(GL_TEXTURE_2D,0,GL_RED,GL_FLOAT,tmp);         
     }
     else
     {
         tmp= new float[textureHeight* textureWidth *3];
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, getSourceTexture());  

        glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_FLOAT,tmp);         
     }

//    glBindBuffer(GL_PIXEL_PACK_BUFFER,pixelBuffer);        
//    glReadPixels(0,0,textureWidth,textureLenght,GL_RED,GL_FLOAT,tmp);
//    
//    glBufferData(GL_PIXEL_PACK_BUFFER,textureLenght* textureWidth * sizeof(float),0,GL_STREAM_READ);
//    GLfloat* ptr = (GLfloat*)glMapBuffer(GL_PIXEL_PACK_BUFFER,GL_READ_ONLY);
//    if(ptr )
//    {
//        memcpy(tmp,ptr,textureLenght* textureWidth * sizeof(float));
//    }
//    glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
//    //load texture to graphic card
//  //  glTexSubImage2D(GL_TEXTURE_2D,0,0,0,  textureWidth, textureLenght,  colorFormat, GL_FLOAT,0); 
//
//
//    glBindBuffer(GL_PIXEL_PACK_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);
    return tmp;
}

void RendToTex::setTexture(const float* data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, getSourceTexture());  
    
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixelBuffer);        

    if(colorFormat == GL_RED)
    {
        glBufferData(GL_PIXEL_UNPACK_BUFFER,textureHeight* textureWidth * sizeof(float),0,GL_STREAM_DRAW);
        GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER,GL_WRITE_ONLY);
        if(ptr )
        {
            memcpy(ptr,data,textureHeight* textureWidth * sizeof(float));
        }        
    }
    else
    {
        glBufferData(GL_PIXEL_UNPACK_BUFFER,textureHeight* textureWidth * sizeof(float) *3 ,0,GL_STREAM_DRAW);
        GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER,GL_WRITE_ONLY);
        
         if(ptr )
        {
            memcpy(ptr,data,textureHeight* textureWidth * sizeof(float)*3);
        }
    }

    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    //load texture to graphic card
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,  textureWidth, textureHeight,  colorFormat, GL_FLOAT,0); 

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);
}

void RendToTex::exit()
{
    glDeleteProgram(shaderID);
    glDeleteBuffers(1,&pixelBuffer);
   glDeleteBuffers(2,&fboBuffer[0]);
    glDeleteTextures(2,&textureBuffer[0]);
}

void RendToTex::reset()
{
    std::vector<float> emtpyData;
    if(colorFormat == GL_RED)
    {
        emtpyData = std::vector<float>(textureWidth*textureHeight,0.0);
    }
    else
    {
        emtpyData = std::vector<float>(textureWidth*textureHeight*3,0.0);
    }
    setTexture(emtpyData.data());
}

void RendToTex::setParameterValue(const std::string& parameter, float value) 
{
    auto itr = std::find_if(v_Uniforms.begin(),v_Uniforms.end(),[&](auto val){return val.second.compare(parameter) == 0;});
    if(itr != v_Uniforms.end())
    {
        itr->first = value;
    }

}

float RendToTex::getParameterValue(const std::string& parameter)
{
    auto itr = std::find_if(v_Uniforms.begin(),v_Uniforms.end(),[&](auto val){return val.second.compare(parameter) == 0;});
    if(itr != v_Uniforms.end())
    {
        return itr->first;
    }
    else
    {
        return 0; //TODO: here we need an exception        
    }
}


ILuint RendToTex::prepareExport()
{
    ilInit();
    std::vector<float> imgData;
    
    //set all data to RGB format
    float* texData = getTexture();
            imgData.resize(textureWidth*textureHeight*3,0.0);
    if(colorFormat == GL_RED)
    {
        

        for(int i = 0, j = 0; i < textureWidth*textureHeight*3; i += 3, ++j)
        {
           imgData[i] = texData[j];
           imgData[i+1] = texData[j];
           imgData[i+2] = texData[j];
        }
    }
    else
    {
        imgData = std::vector<float>(texData,texData+(textureWidth*textureHeight*3));
    }
    
    //set all values between 0 and 1
     float lowest = *std::min_element(imgData.begin(), imgData.end());
    float highest = *std::max_element(imgData.begin(), imgData.end());
    
    if(lowest < 0.0)
    {
        lowest = -lowest;
        highest = highest + lowest;
        std::for_each(imgData.begin(),imgData.end(),[&](auto& f){ f+= lowest;});
    }

    std::for_each(imgData.begin(),imgData.end(), [&](auto& value) {value = (value - lowest) / (highest - lowest);});
    
    ILuint id;
        ilGenImages(1, &id);

    ilBindImage(id);
    ilTexImage(textureWidth,textureHeight,1,3,IL_RGB,IL_FLOAT,imgData.data());
    
    ilConvertImage(IL_RGB,IL_UNSIGNED_BYTE);

    
    return id;
}

void RendToTex::setEnable(GLboolean enable)
{
    this->enable = enable;
}

