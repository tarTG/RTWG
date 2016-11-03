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
#include "TextureLoader.h"
#include "ShaderLoader.h"

class WaterRender
{
public:
    WaterRender(const GLuint vao_plane,const float gridVertices, const glm::ivec2& gridDimensions);

    void init(const std::string& shaderPath,const std::string& normalTexturePath);
    
    void render();
    
    void exit();
    
private:
    GLuint waterProgram,vao_plane, waterNormals;
    glm::ivec2 gridDimensions;
    float gridVertices;

};

#endif /* WATERRENDER_H */

