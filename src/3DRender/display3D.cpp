/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   display3D.cpp
 * Author: tg
 * 
 * Created on 3. November 2016, 10:51
 */



#include <AntTweakBar.h>
#include <chrono>
#include <future>

#include "display3D.h"
#include "simpleRender.h"
#include "simulation.h"

display3D::display3D(const uint32_t windowLenght, const uint32_t windowHeight, const uint32_t textureLenght, const uint32_t textureHeight) 
 : windowDimension(glm::ivec2(windowLenght,windowHeight)), textureDimension(glm::ivec2(textureLenght,textureHeight))
{
}


void display3D::init() 
{
    initCamera();
    

    terrainPlain = std::make_shared<plane>(glm::ivec2(80,80),glm::vec3(0.0),glm::vec3(0.0),glm::vec3(1.0));

    landscaperender = std::make_shared<landscapeRender>(terrainPlain);
    shadows = std::make_shared<Shadows>(terrainPlain);
    waterRender =  std::make_shared<WaterRender>(terrainPlain,textureDimension);
    light = std::make_shared<Light>( 0,glm::vec3(0),glm::vec3(40));
    
    Bar3D = inputHandler::createNewBar("3DControls","position='608 8' size='200 200'");
    TwAddVarRW(Bar3D,"Light Position",TW_TYPE_DIR3F,&(light->getCurrentData().Position),"opened='true'");
   // TwAddVarRW(Bar3D,"Light Color",TW_TYPE_COLOR3F,&(light->getCurrentData().Color),"");    
    TwAddVarRW(Bar3D,"Height Factor",TW_TYPE_FLOAT,&(heightFactor)," min=0.1 max = 6.0 step = 0.1" ); 
    
     glBindVertexArray(terrainPlain->getVao_plane());

    landscaperender->init(std::string(SHADER_PATH) + "display/3D/dispmap");
    shadows->init(std::string(SHADER_PATH) +  "display/3D/Shadow");
    waterRender->init(std::string(SHADER_PATH) +  "display/3D/waterDispmap",std::string(RESOURCES_PATH) + "grass_normals.png",Bar3D);
     glBindVertexArray(0);
     

}

void display3D::render(float frameTime,simulation* sim)
{
    
    sim->setTexturesBindings();
    
    camera->Update(frameTime);
        //0891A = GL_CLAMP_VERTEX_COLOR, 0x891B = GL_CLAMP_FRAGMENT_COLOR
    glClampColor(0x891A, GL_FALSE);
    glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
    glClampColor(0x891B, GL_FALSE);
     glBindVertexArray(terrainPlain->getVao_plane());
    
    
    shadows->render(heightFactor,light->getCurrentData().Position);
    camera->setViewport(0.0,0.0,windowDimension.x,windowDimension.y);
    camera->loadViewPort();
    landscaperender->render(camera,shadows,light,sim->getCurrentDisplay(),heightFactor);
    waterRender->render(camera,shadows,light,frameTime,heightFactor);
    
        glBindVertexArray(0);
        glClampColor(0x891A, GL_TRUE);
    glClampColor(GL_CLAMP_READ_COLOR, GL_TRUE);
    glClampColor(0x891B, GL_TRUE);
    sim->unsetTexturesBindings();
    
}

void display3D::initCamera()
{
    camera = std::make_unique<Camera>();
   camera->setClipping(0.5f,10000.0f);
   camera->SetMove_camera(true);
   camera->SetCamera_look_at(glm::vec3(-5.0,2.0,5.0));
   camera->setViewport(0, 0, windowDimension.x, windowDimension.y);
   camera->SetField_of_view(55.0f);
   camera->SetCamera_position(glm::vec3(2.0,2.0,1.0));
}

void display3D::handleCameraInput(GLFWwindow* window)
{
        glm::dvec2 newpos;
        glfwGetCursorPos(window, &newpos.x, &newpos.y);
        

        
    if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT)== GLFW_PRESS)
    {
        camera->MoveHead((prevMousePosition.x -newpos.x)*-0.01,(prevMousePosition.y-newpos.y)*0.01);
    }
        prevMousePosition = newpos;
        if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
        {
            camera->MoveX(-0.7);
        }
        if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
        {
            camera->MoveX(0.7);
        }
        if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
        {
            camera->MoveZ(-0.7);
        }        
        if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
        {
            camera->MoveZ(0.7);
        }          
        //ugly workaround for bug in GLFW3
        if(glfwGetKey(window,GLFW_KEY_TAB) == GLFW_PRESS && ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - buttonWait)).count() > 200))
        {
                buttonWait = std::chrono::steady_clock::now() ;
                render3D = !render3D;

        }

       
}

bool display3D::isRender3D() const
{
    return render3D;
}



