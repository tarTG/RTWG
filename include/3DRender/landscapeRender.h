/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   landscapeRender.h
 * Author: tg
 *
 * Created on 2. November 2016, 11:50
 */

#ifndef LANDSCAPERENDER_H
#define LANDSCAPERENDER_H

#include <GL3W/gl3w.h>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IL/il.h>
#include "TextureLoader.h"
#include "ShaderLoader.h"
#include <memory>
#include "plane.h"
#include "Shadows.h"
#include "Camera.h"
#include "Light.h"

class landscapeRender 
{
public:
    landscapeRender(std::shared_ptr<plane> terrainPlain);

    void init(const std::string& shaderPath);
    
    void render(std::shared_ptr<Camera> camera, std::shared_ptr<Shadows> shadow,std::shared_ptr<Light> light,const uint32_t currentDisplay);
    
    void exit();
    
private:
    std::shared_ptr<plane> terrainPlain;
    GLuint displayProgram;

};

#endif /* LANDSCAPERENDER_H */

