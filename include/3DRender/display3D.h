/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   display3D.h
 * Author: tg
 *
 * Created on 3. November 2016, 10:51
 */

#ifndef DISPLAY3D_H
#define DISPLAY3D_H
#include <GL3W/gl3w.h>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IL/il.h>
#include <memory>
#include "TextureLoader.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "landscapeRender.h"
#include "WaterRender.h"
#include "Shadows.h"
#include "Light.h"
class display3D 
{
public:
    display3D(const uint32_t windowLenght,const uint32_t windowHeight,
                const uint32_t textureLenght,const uint32_t textureHeight);
    
    void init();
    
    void render();

private:
    void generatePlane(int width, int height);
    void initCamera();
    std::unique_ptr<landscapeRender> landscaperender;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<WaterRender> waterRender;
    std::unique_ptr<Shadows> shadows;
    std::unique_ptr<Light> light;
    GLuint vbo_plane, vao_plane, vbo_indexbuffer;
    glm::ivec2 windowDimension;
    glm::ivec2 textureDimension;
    uint32_t planeVertices;

};

#endif /* DISPLAY3D_H */

