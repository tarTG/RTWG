/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simpleRender.h
 * Author: tartg
 *
 * Created on 18. Oktober 2016, 10:08
 */

#ifndef SIMPLERENDER_H
#define SIMPLERENDER_H

#include "GL3W/gl3w.h"
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>
#include <string>

/*
 *  Class to handle simple render stuff
 */
class simpleRender 
{
public:
    /**
     * Constructor for simpleRender
     * @param windowLength - lenght of the window
     * @param windowHeight - height of the window
     * @param windowTitle - titel of the window
     */
    simpleRender(uint32_t windowLength, uint32_t windowHeight,std::string windowTitle);
    
    /**
     * initialize GLFW, GL3W, OpenGL context and window
     */
    uint32_t init();
    
    /**
     * clear content of the window
     */
    void clearWindow();
    
    /**
     * swap buffers and poll events
     */
    void render();
    
    /**
     * close OpenGL context and window
     */
    void exit();
    
    /**
     * get Pointer to the window
     */
    GLFWwindow* getWindow() const;
    



private:
        uint32_t windowHeight,windowLength; //window dimensions
    std::string windowTitle; //window title
    GLFWwindow* window; //window refrence
};

#endif /* SIMPLERENDER_H */

