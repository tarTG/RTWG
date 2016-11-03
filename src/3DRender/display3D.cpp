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



#include "display3D.h"

display3D::display3D()
{
}




void display3D::initCamera(const uint32_t windowLenght,const uint32_t windowHeight)
{
    camera = std::make_unique<Camera>();
   camera->setClipping(0.5f,10000.0f);
   camera->SetMove_camera(true);
   camera->SetCamera_look_at(glm::vec3(1.0,10.0,1.0));
   camera->setViewport(0, 0, windowLenght, windowHeight);
   camera->SetField_of_view(55.0f);
   camera->SetCamera_position(glm::vec3(2.0,10.0,1.0));
}


void display3D::generatePlane(int width, int height)
{

    std::vector<GLfloat> vertices = std::vector<GLfloat>((width)*(height)*3,0.0);
    std::vector<GLuint> indices = std::vector<GLuint>((width-1)*(height-1)*6);

      unsigned  int index = 0;

    for (int x = 0; x < width; x++)
    {
        for (int z = 0; z < ((height)*3); z+=3)
        {
            vertices[index++] = (GLfloat)x; 
            vertices[index++] =(GLfloat) 0.0f;
            vertices[index++] = (GLfloat)(z/3.0);
        }
    }       

       index = 0;

    for (unsigned int x = 0; x < width-1 ; x++)
    {
       for (unsigned int z = 0; z < height-1; z++)
       {
            unsigned int offset = x * height + z;
            indices[index] = (offset + 1);
            indices[index + 1] = (offset + 0);
            indices[index + 2] = (offset + height+1);
            indices[index + 3] = (offset + height);
            index += 4;
        }
    }
    glGenVertexArrays(1, &vao_plane);
    glBindVertexArray(vao_plane);
    glPatchParameteri(GL_PATCH_VERTICES,3);
    glGenBuffers(1,  &vbo_plane);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_plane);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),vertices.data(), GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

     glGenBuffers(1, &vbo_indexbuffer);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indexbuffer);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

     planeVertices = indices.size();
    glBindBuffer(GL_ARRAY_BUFFER, 0); //free buffer
    glBindVertexArray(0);     
}