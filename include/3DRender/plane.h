/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   plane.h
 * Author: tg
 *
 * Created on 4. November 2016, 10:06
 */

#ifndef PLANE_H
#define PLANE_H

#include <GL3W/gl3w.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

class plane {
public:
    plane(glm::ivec2 planeDimension, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    uint32_t getPlaneVertices() const;

    glm::ivec2 getPlaneDimension() const;

    GLuint getVao_plane() const;
    
    glm::fmat4 getModel_matrix() const;
    
    glm::vec3 getScale() const;
    
    void setScale(const glm::vec3 scale);
    
    


private:
    
   void generatePlane(int width, int height);
   
    glm::fmat4 model_matrix;
    glm::mat4 scaleMat;
    glm::vec3 scaleVec;
    
    GLuint  vbo_plane,vao_plane, vbo_indexbuffer;
    glm::ivec2 planeDimension;
    uint32_t planeVertices;


};

#endif /* PLANE_H */

