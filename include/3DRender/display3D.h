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
#include "plane.h"
#include "inputHandler.h"
#include "simulation.h"
class display3D 
{
public:
    display3D(const uint32_t windowLenght,const uint32_t windowHeight,
                const uint32_t textureLenght,const uint32_t textureHeight);
    
    void init();
    
    void render(float frameTime,simulation* sim);
    
        void handleCameraInput(GLFWwindow* window);
    bool isRender3D() const;

private:

    void initCamera();

    std::shared_ptr<landscapeRender> landscaperender;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<WaterRender> waterRender;
    std::shared_ptr<Shadows> shadows;
    std::shared_ptr<Light> light;
    std::shared_ptr<plane> terrainPlain;
 
    bool render3D = true;
    glm::dvec2 prevMousePosition = glm::dvec2(0.0);
    glm::ivec2 windowDimension;
    glm::ivec2 textureDimension;
    GLuint  vao;
    TwBar* Bar3D;
    float heightFactor = 1.0;

};

#endif /* DISPLAY3D_H */

