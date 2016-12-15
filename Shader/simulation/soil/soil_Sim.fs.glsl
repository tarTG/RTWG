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

uniform float errodeFactor = 1;
uniform float soilDiffuseFactor = 1;
out vec3 color;


vec3 getTexValue(sampler2D tex, float x, float y)
{
    return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;
}

float getGround(float x, float y)
{
    return getTexValue(rock,x,y).x + getTexValue(soil,x,y).x;

}


   float exchange(float g1, vec3 l1, float x, float y)
{
    float g2 = getTexValue(rock,x, y).x;
    vec3 l2 = getTexValue(soil, x, y);
    float change = ( (g2+l2.x)-(g1+l1.x))*0.125 ;
   change = clamp(change, -l1.x/2.0, l2.x/2.0)*0.08;
    return change;
}

void main() {

    float tf = 0.0015;
    float tm = 0.5;


    vec3 g = getTexValue(soil, 0.0, 0.0);
    vec3 g1 = getTexValue(rock, 0.0, 0.0);

    vec3 w = getTexValue(water, 0.0, 0.0);

     float erroded = (length(w.yz)*0.00004 * errodeFactor)/(w.x+0.001);
        erroded /= 1.0 + g.x*300.0;
        erroded = clamp(erroded,0.0,g1.x);
        g.y = erroded;
        g.x += erroded;


        vec3 w_left    = getTexValue(water, -1.0,  0.0);
        vec3 w_right   = getTexValue(water,  1.0,  0.0);
        vec3 w_top     = getTexValue(water,  0.0,  1.0);
        vec3 w_bot     = getTexValue(water,  0.0, -1.0);

        vec3 g_left    = getTexValue(soil, -1.0,  0.0);
        vec3 g_right   = getTexValue(soil,  1.0,  0.0);
        vec3 g_top     = getTexValue(soil,  0.0,  1.0);
        vec3 g_bot     = getTexValue(soil,  0.0, -1.0);

   float soil_transported_off = (min(abs(w.y*tf/(w.x+0.001)), tm) + min(abs(w.z*tf/(w.x+0.001)), tm))*g.x;

        float soil_transported_in = (
        clamp(w_left.y*tf/(w_left.x+0.001), 0.0, tm) * g_left.x +
        clamp(-w_right.y*tf/(w_right.x+0.001), 0.0, tm) * g_right.x +
        clamp(-w_top.z*tf/(w_top.x+0.001), 0.0, tm) * g_top.x +
        clamp(w_bot.z*tf/(w_bot.x+0.001), 0.0, tm) * g_bot.x
        );
       g.x += (soil_transported_in- soil_transported_off ) ;
    
           g.x = max(0.0,g.x) ;
  float c = (
        exchange(g1.x,g, 1.0,  0.0) +
        exchange(g1.x,g, -1.0,  0.0) +
        exchange(g1.x,g,  0.0,  1.0) +
        exchange(g1.x,g,  0.0, -1.0)
    );
   g.x  += (c *soilDiffuseFactor);

   
   
   /* if(g.x > 0.2) //if soil threashold is reached
    {
       g.x -= 0.001; //add to landmass
       g.y += 0.001;
    }*/

//        g.x = max(0.0,g.x) ;

    color =  g;

 
}
