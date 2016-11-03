/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Light.cpp
 * Author: tg
 * 
 * Created on 3. November 2016, 10:55
 */

#include "Light.h"

Light::Light(Light_Data::LightID id, glm::vec3& Color, const Light_Data::position Position) :
currentData({id,Color,Position})
{
}

void Light::changeColor(const glm::vec3& Color)
{
    currentData.Color = Color;
}

void Light::changePosition(const Light_Data::position& Position)
{
    currentData.Position = Position;
}

