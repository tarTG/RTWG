/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simpleRender.cpp
 * Author: tartg
 * 
 * Created on 18. Oktober 2016, 10:09
 */

#include "simpleRender.h"




simpleRender::simpleRender(u_int32_t windowLength, uint32_t windowHeight, std::string windowTitle) :
windowHeight(windowHeight),windowLength(windowLength), windowTitle(windowTitle)
{
}

u_int32_t simpleRender::init() 
{
    if (!glfwInit()) //try to init glfw
          return 1;

    //set OpenGL context to Version 4.4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //create Window
    window = glfwCreateWindow(windowLength, windowHeight, windowTitle.c_str(), NULL, NULL);
    if (!window) //if window does not exist
    {
        glfwTerminate(); //close context
        return 1;
    }
    //set context to window
    glfwMakeContextCurrent(window);
            glfwSwapInterval(0);

    if(gl3wInit() !=  0)   //init gl3w
    {
        glfwTerminate();
        return 1;
    }
    return 0;
}

void simpleRender::clearWindow() 
{
            glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);     
        glCullFace(GL_BACK);

    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );    //clear Color buffer and Depth Buffer
        const GLfloat black[] = {116.f/255.0,208.f/255.0,241.f/255.0, 1.0f };
    const GLfloat ones[] = { 1.0f };    
    glClearBufferfv(GL_COLOR, 0,black);
    glClearBufferfv(GL_DEPTH, 0, ones);

}


void simpleRender::render()
{
    /* Swap front and back buffers */
    glfwSwapBuffers(window);


    /* Poll for and process events */
     glfwPollEvents();
}



void simpleRender::exit()
{
    glfwDestroyWindow(window);//destryo window
    glfwTerminate(); //exit glfw
}

GLFWwindow* simpleRender::getWindow() const 
{
    return window;
}

