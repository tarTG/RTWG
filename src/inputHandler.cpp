/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   inputHandler.cpp
 * Author: tartg
 * 
 * Created on 18. Oktober 2016, 10:35
 */

#include <functional>

#include "inputHandler.h"

static void windowSizeCallback(GLFWwindow*,int newWidth, int newHeight)
{
    TwWindowSize(newWidth, newHeight);glViewport(0, 0, newWidth, newHeight);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    TwEventMouseButtonGLFW(button,action);
}
static void cursorPosCallback(GLFWwindow* window, double x, double y)
{
    TwEventMousePosGLFW((int)x,(int)y);
}

static void scrollCallback(GLFWwindow* window, double x, double y)
{
    static double lastscrollPos = 0;
    lastscrollPos += y;
    TwEventMouseWheelGLFW(lastscrollPos );
}

static void keyCallback(GLFWwindow* window,int key, int scancode, int action, int mods)
{
    TwEventKeyGLFW(key,action);
}

static void charCallback(GLFWwindow* window,unsigned int codepoint)
{
    TwEventCharGLFW(codepoint,1);
}


inputHandler::inputHandler(GLFWwindow* window) : window(window)
{
    //get window dimensions
    int width,height;
     	glfwGetWindowSize(window,&width, &height);
    // Initialize AntTweakBar
    TwInit(TW_OPENGL_CORE, NULL);
     TwWindowSize(width, height); 
    
    
    // Set GLFW event callbacks
    // - Redirect window size changes to the callback function WindowSizeCB
    glfwSetWindowSizeCallback(window,windowSizeCallback);
    // - Directly redirect GLFW mouse button events to AntTweakBar
    glfwSetMouseButtonCallback(window,mouseButtonCallback);
    // - Directly redirect GLFW mouse position events to AntTweakBar
    glfwSetCursorPosCallback(window,cursorPosCallback);
    // - Directly redirect GLFW mouse wheel events to AntTweakBar
    glfwSetScrollCallback(window,scrollCallback); 
    // - Directly redirect GLFW key events to AntTweakBar
    glfwSetKeyCallback(window,keyCallback);
    // - Directly redirect GLFW char events to AntTweakBar
    glfwSetCharCallback(window,charCallback);
}

TwBar* inputHandler::createNewBar(const std::string& description) 
{
    return TwNewBar(description.c_str());
}


void inputHandler::update() 
{
    // Draw tweak bars
    TwDraw();

}


void inputHandler::exit() 
{
    TwTerminate();
}




