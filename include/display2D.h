/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   display2D.h
 * Author: tg
 *
 * Created on 27. Oktober 2016, 10:55
 */

#ifndef DISPLAY2D_H
#define DISPLAY2D_H

#include "GL3W/gl3w.h"
#include <GLFW/glfw3.h>
#include <array>
#include "ShaderLoader.h"


class display2D {
public:
    display2D(const std::string& shaderPath);

    void render(std::array<GLint,2> windowDimensions, unsigned int currentSelection, GLuint textureID);
   
    void exit();
private:
    GLuint displayProgram, vao;
    
};

#endif /* DISPLAY2D_H */

