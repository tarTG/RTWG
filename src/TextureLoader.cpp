/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextureLoader.cpp
 * Author: tg
 * 
 * Created on 14. Januar 2016, 12:50
 */

#include <IL/il.h>
#include <IL/ilu.h>
#include <GL3W/gl3w.h>
#include "TextureLoader.h"
#include <RTplatec/include/FractalGenerator.h>


GLuint TextureLoader::load2DTexture(const std::string& fileName, const GLuint OUTcolorFormat, const GLuint OUTvalueFormat,
                                                                const ILint INcolorFormat, const ILint INvalueFormat)
{
   ILuint imgID =0;                                  //id of the image
   ilInit(); //init DevIL

   GLuint textureID;
   
    ilGenImages(1,&imgID);       //generate image ID
    glGenTextures(1,&textureID);  //generate Texture ID
    ilBindImage(imgID);         //bind Image


    //some devIL options
    ilEnable(IL_ORIGIN_SET);    
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    if(ilLoadImage(fileName.c_str())) //try to load image
    {
        if(!ilConvertImage(INcolorFormat,INvalueFormat))
            return 0;  //convert image

       glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //setup Opengl Texture
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 

        //load texture                    

      glTexImage2D(GL_TEXTURE_2D,0,OUTcolorFormat, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, OUTcolorFormat, OUTvalueFormat,ilGetData()); 
         glBindTexture(GL_TEXTURE_2D, 0);
    }
    else //if image loading didn't work. print error
    {
     std::stringstream s;        
     s <<"Could not load texture " << fileName.c_str();
     std::cout  << s.str()<< std::endl;
    }                    
        
   
    ilDeleteImage(imgID); //delete image
    return textureID;
}

GLuint TextureLoader::load2DTextureArray(const std::vector<std::string>& fileNames, const GLuint OUTcolorFormat, const GLuint OUTvalueFormat, const ILint INcolorFormat, const ILint INvalueFormat)
{
    ILuint imgID =0;                                  //id of the image
    ilInit(); //init DevIL
    ilGenImages(1,&imgID);       //generate image ID
    ilBindImage(imgID);         //bind Image
    GLuint textureID;

    glGenTextures(1,&textureID);  //generate Texture ID
 
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
    unsigned int index = 0;
    
    for(auto fileName : fileNames)
    {


        if(ilLoadImage(fileName.c_str())) //try to load image
        {
            ilEnable(IL_ORIGIN_SET);    
            ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    
                if(!ilConvertImage(INcolorFormat,INvalueFormat))
                {
                    std::stringstream s;        
                    s <<"Could not convert texture " << fileName.c_str();
                    std::cout  << s.str()<< std::endl;
                    continue;
                }
                 iluScale(1024,1024,ilGetInteger(IL_IMAGE_DEPTH));
                if(index == 0)
                {
                        glTexImage3D(GL_TEXTURE_2D_ARRAY,0,  OUTcolorFormat,ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),fileNames.size(),0,OUTcolorFormat, OUTvalueFormat, 0);
                }

                glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //setup Opengl Texture
                glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
                glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_REPEAT); //setup Opengl Texture
                glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_REPEAT);    
                //load texture                  

                glTexSubImage3D(GL_TEXTURE_2D_ARRAY,0,0,0,index, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 1, OUTcolorFormat, OUTvalueFormat,ilGetData()); 

               }
            else //if image loading didn't work. print error
            {
                    std::stringstream s;        
                    s <<"Could not load texture " << fileName.c_str();
                    std::cout  << s.str()<< std::endl;
            }         
            ++index;

    }
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    ilDeleteImage(imgID); //delete image
    return textureID;

}






GLuint TextureLoader::loadEmpty2DTexture(const int width, const int lenght, const GLuint OUTcolorFormat, const GLuint OUTvalueFormat, const GLuint interplolation)
{
     //load texture                    
//    std::vector<float> data(width *lenght * 3,0.0);
    
   GLuint textureID;

    glGenTextures(1,&textureID);  //generate Texture ID

    glBindTexture(GL_TEXTURE_2D, textureID);

     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,interplolation); //setup Opengl Texture
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,interplolation); 
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER); //setup Opengl Texture
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);    
//    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F, width, lenght, 0, OUTcolorFormat, OUTvalueFormat,nullptr); 
            if(OUTcolorFormat == GL_RED)
            {
                glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, width, lenght);
            }
            else
            {
           glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, width, lenght);
            }
    glBindTexture(GL_TEXTURE_2D, 0);


    return textureID;
}

GLuint TextureLoader::generateNoiseTexture(const int width, const int lenght,const int seed, const float roughness,const int turbulence)
{
    GLuint noiseID;
    
    std::vector<float> noiseMap = std::vector<float>(width *lenght,0.0);
    FractalGenerator::noiseTurbulence(noiseMap.data(),width,lenght,seed,roughness,turbulence);
    const float lowest = *std::min_element(noiseMap.begin(), noiseMap.end());
    const float highest = *std::max_element(noiseMap.begin(), noiseMap.end());
    const float medium = highest - lowest;
    
    std::for_each(noiseMap.begin(), noiseMap.end(), [&](auto& value) {value = (value - lowest) / medium;});

    glGenTextures(1,&noiseID);  //generate Texture ID

    glBindTexture(GL_TEXTURE_2D, noiseID);

     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //setup Opengl Texture
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 

        glTexImage2D(GL_TEXTURE_2D,0,GL_RED, width, lenght, 0, GL_RED, GL_FLOAT,noiseMap.data()); 
   
    glBindTexture(GL_TEXTURE_2D, 0);    
    return noiseID;
}


ILuint TextureLoader::SaveTexture(ILuint Width, ILuint Height, std::string FileName, ILuint Texture)
{
    ilEnable(IL_FILE_OVERWRITE);


    ilBindImage(Texture);



    ilSave(IL_PNG, FileName.c_str());

    ilDisable(IL_FILE_OVERWRITE);

    if(ilGetError() != IL_NO_ERROR)
        return ilGetError();

    return IL_NO_ERROR;
} 