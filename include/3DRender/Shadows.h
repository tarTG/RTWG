/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Shadows.h
 * Author: tg
 *
 * Created on 2. November 2016, 11:51
 */

#ifndef SHADOWS_H
#define SHADOWS_H

#include <GL3W/gl3w.h>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderLoader.h"
#include "plane.h"

#include <memory>


class Shadows 
{
public:
    Shadows(std::shared_ptr<plane> terrainPlain );

    void init(const std::string& shaderPath);
    void exit();
    void render(const glm::vec3& lightPosition);
    
    const glm::mat4 getBiasedDepthMVP();
    
    GLuint getDepthTexture() const;
    
    
    
private:
    GLuint shaderID, depthFBO, depthTexture;
    glm::mat4 depthMVP;
    std::shared_ptr<plane> terrainPlain;

};

#endif /* SHADOWS_H */

