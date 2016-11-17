/*
 * Sample dummy shader to check the highlighter plugin.
 */

#version 430 core


layout (binding = 0) uniform sampler2D rock;
layout (binding = 1) uniform sampler2D soil;
layout (binding = 2) uniform sampler2D water;
layout (binding = 3) uniform sampler2D temp;
layout (binding = 4) uniform sampler2D moist;
layout (binding = 5) uniform sampler2D wind;
layout (binding = 6) uniform sampler2D ice;

out vec3 color;

uniform float iceTemperature;


vec3 getTexValue(sampler2D tex, float x, float y)
{
    return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;
}

float getGround(float x, float y)
{
    return getTexValue(rock,x,y).x + getTexValue(soil,x,y).x;

}


float exchange(float g1, float l1,  vec2 dir)
{
    float g2 = getGround(dir.x, dir.y);
    float l2 = getTexValue(ice, dir.x, dir.y).x;
    float change = g2 -g1;
   return clamp(change, -l1*0.01, l2*0.01);
     
}


void main() 
{
    vec2 top = vec2(0,1), bot = vec2(0,-1), left = vec2(-1,0), right = vec2(1,0), current= vec2(0,0);


    float newIce = getTexValue(ice,0,0).x;
    float temperature = getTexValue(temp,0,0).x;
    float ground =  getGround(0,0);
    float melt = 0.0;
    if((temperature < iceTemperature))
        newIce += mix(0.002,0.007,abs(temperature));
    else
    {
        newIce -= mix(0.002,0.007,abs(temperature));
         melt = clamp(abs(clamp(newIce,0.0,1.0)-getTexValue(ice,0,0).x),0.0,1.0);
      }

    float v = (
        exchange(ground, newIce,  top) +
        exchange(ground, newIce,  bot) +
        exchange(ground, newIce,  left) +
        exchange(ground, newIce, right)
    );


       newIce = newIce + v;
        newIce = clamp(newIce,0.0,1.0);
     color = vec3(newIce,melt ,0.00);

}
