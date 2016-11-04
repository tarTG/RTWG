/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   plane.cpp
 * Author: tg
 * 
 * Created on 4. November 2016, 10:06
 */

#include "plane.h"

plane::plane(glm::ivec2 planeDimension,glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
:planeDimension(planeDimension) ,scaleVec(scale)
{
    model_matrix = glm::translate(glm::mat4(1.0f), position);
    
    model_matrix = glm::rotate(model_matrix, rotation.x,glm::fvec3(1.0f,0.0f,0.0f));
    model_matrix = glm::rotate(model_matrix, rotation.y,glm::fvec3(0.0f,1.0f,0.0f));
    model_matrix = glm::rotate(model_matrix, rotation.z,glm::fvec3(0.0f,0.0f,1.0f));    

    model_matrix *= glm::scale(scale);
    
    generatePlane(planeDimension.x, planeDimension.y);

}

glm::ivec2 plane::getPlaneDimension() const
{
    return planeDimension;
}

uint32_t plane::getPlaneVertices() const
{
    return planeVertices;
}

GLuint plane::getVao_plane() const
{
    return vao_plane;
}

glm::fmat4 plane::getModel_matrix() const
{
    return model_matrix;
}

glm::vec3 plane::getScale() const
{
    return scaleVec;
}

void plane::setScale(const glm::vec3 scale)
{
    scaleMat = glm::scale(glm::mat4(1.0f), scale / scaleVec);
    model_matrix = model_matrix* scaleMat;
    scaleVec = scale;
}



void plane::generatePlane(int width, int height)
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
    glPatchParameteri(GL_PATCH_VERTICES,4);
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