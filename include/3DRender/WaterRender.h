/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WaterRender.h
 * Author: tg
 *
 * Created on 2. November 2016, 11:49
 */

#ifndef WATERRENDER_H
#define WATERRENDER_H

#include <GL3W/gl3w.h>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IL/il.h>
#include <AntTweakBar.h>
#include "RendToTex.h"
#include "TextureLoader.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "Shadows.h"
#include "Light.h"

class WaterRender
{
public:
    WaterRender(std::shared_ptr<plane> terrainPlain,const glm::ivec2& textureDimension);

    void init(const std::string& shaderPath,const std::string& normalTexturePath, TwBar* Bar3d);
    
    void render(std::shared_ptr<Camera> camera, std::shared_ptr<Shadows> shadows, std::shared_ptr<Light> light, const float time,const float heightFactor);
    
    void exit();
    
private:
    GLuint waterProgram, waterNormals;
    std::shared_ptr<plane> terrainPlain;
    std::unique_ptr<RendToTex> waterFlows;
    glm::ivec2 textureDimension;
    float movementTime = 0.f;

};

#endif /* WATERRENDER_H */

