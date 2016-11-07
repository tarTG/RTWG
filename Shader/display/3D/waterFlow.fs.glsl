
#version 430 core

out vec3 color;

layout (binding = 0) uniform sampler2D rock;
layout (binding = 1) uniform sampler2D soil;
layout (binding = 2) uniform sampler2D water;
layout (binding = 3) uniform sampler2D temp;
layout (binding = 4) uniform sampler2D moist;
layout (binding = 5) uniform sampler2D wind;
layout (binding = 6) uniform sampler2D ice;

layout (binding = 9) uniform sampler2D flows;


vec3 getTexValue(sampler2D tex, float x, float y)
{
    return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;
}


void main() 
{
   color = vec3(getTexValue(flows,0.0,0.0).xy + ((getTexValue(water, 0,0).yz)*0.001)/(getTexValue(water, 0,0).x*0.1+0.001),0.0);
}
