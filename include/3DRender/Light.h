/* 
 * File:   LightManager.h
 * Author: tg
 *
 * Created on 23. April 2015, 01:53
 */

#ifndef LIGHTMANAGER_H
#define	LIGHTMANAGER_H

#include <vector>
#include <algorithm>
#include <array>
#include <glm/glm.hpp>


struct  Light_Data
{
    typedef glm::vec3 position;
    typedef uint32_t LightID;
    LightID id;
    glm::vec3 Color;
    position Position;

};

class Light 
{
public:   
    
    /**
     * Add light into szene
     * @param id - id of the Light
     * @param Color - color of the Light
     * @param Position - Position of the Light
     */
    Light(Light_Data::LightID id,glm::vec3& Color,const Light_Data::position Position);
    
    
    /**
     * Change Color of the light
     * @param id - id of the light
     * @param Color - the new color
     */
    void changeColor(const glm::vec3& Color);
    
    /**
     * Change Position of the Light 
     * @param id - id of the light
     * @param Position - new Position
     */
    void changePosition(const Light_Data::position& Position);

private:

    
    Light_Data currentData; ///< vector of all lights

};
#endif