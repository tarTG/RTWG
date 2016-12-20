/*
 * Sample dummy shader to check the highlighter plugin.
 */

#version 430 core

uniform float min_therm_limit = 1;
uniform float max_therm_limit = 1;

uniform float threm_factor = 2;

layout (binding = 0) uniform sampler2D rock;
layout (binding = 1) uniform sampler2D soil;
layout (binding = 2) uniform sampler2D water;
layout (binding = 3) uniform sampler2D temp;
layout (binding = 4) uniform sampler2D moist;
layout (binding = 5) uniform sampler2D wind;
layout (binding = 6) uniform sampler2D ice;

layout (location = 0) out float color;

vec3 getTexValue(sampler2D tex, float x, float y)
{
    return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;
}
float getGround(float x, float y)
{
    return getTexValue(rock,x,y).x + getTexValue(soil,x,y).x;

}


float thermal_erosion( float h1, float x, float y)
{

    float h2 = getTexValue(rock, x, y).x;
    float diff = 0.0; 
    if(abs(h2-h1) <  max_therm_limit && abs(h2-h1) >  min_therm_limit && getTexValue(water, 0, 0).x < 0.05)
    {
        diff = (h2-h1)/8.0;
    }
    return diff*threm_factor*0.04;
}


void main() 
{
    color = texture2D(rock, (gl_FragCoord.xy)/textureSize(rock,0)).x; //get height
   color -= getTexValue(soil,0,0).y ;   //subtract new generated soil

    if(threm_factor > 0.0)
    {
        color += thermal_erosion(color, 0.0, 1.0) + thermal_erosion(color, 0.0, -1.0);
        color += thermal_erosion(color, 1.0, 0.0) + thermal_erosion(color, - 1.0, 0.0);
        color += (thermal_erosion(color, 1.0, 1.0) + thermal_erosion(color, - 1.0, 1.0))*0.25;
        color += (thermal_erosion(color, 1.0, -1.0) + thermal_erosion(color, - 1.0, - 1.0))*0.25;
    }
     


    color = max(0.001,color);

}
