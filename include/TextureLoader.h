/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextureLoader.h
 * Author: tg
 *
 * Created on 14. Januar 2016, 12:50
 */

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "../3rdParty/GL3W/gl3w.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <IL/il.h>
#include <vector>

class TextureLoader {
public:

    static GLuint load2DTexture(const std::string& fileName, const GLuint OUTcolorFormat, const GLuint OUTvalueFormat,
                                                                const ILint INcolorFormat, const ILint INvalueFormat);
    
    static ILuint load2DTexture(const std::string& fileName, const ILint INcolorFormat, const ILint INvalueFormat);
    
    static GLuint loadEmpty2DTexture(const int width, const int lenght, const GLuint OUTcolorFormat, const GLuint OUTvalueFormat, const GLuint interplolation = GL_NEAREST);    
    
    static GLuint load2DTextureArray(const std::vector<std::string>& fileNames, const GLuint OUTcolorFormat, const GLuint OUTvalueFormat,
                                                                const ILint INcolorFormat, const ILint INvalueFormat);
    
    static GLuint generateNoiseTexture(const int width, const int lenght,const int seed, const float roughness,const int turbulence);  
    
  static ILuint SaveTexture(ILuint Width, ILuint Height, std::string FileName, ILuint Texture);
private:

};

#endif /* TEXTURELOADER_H */

