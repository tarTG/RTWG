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

class landscapeRender 
{
public:
    landscapeRender(GLuint vao_plane, uint32_t drawSize, const glm::ivec2 gridDimensions);

    void init(const std::string& shaderPath);
    
    void render(const uint32_t currentDisplay,const glm::mat4 depthMVP,GLuint depthTexture, float heightFactor);
    
    void exit();
    
private:
    GLuint displayProgram;
    glm::ivec2 gridDimensions;
    GLuint vao_plane;
    uint32_t drawSize;
};

#endif /* LANDSCAPERENDER_H */

