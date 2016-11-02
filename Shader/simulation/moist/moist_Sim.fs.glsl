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


uniform float waterAddFactor = 1;
uniform float landRemoveFactor = 1;


vec3 getTexValue(sampler2D tex, float x, float y)
{
    vec2 absCorrd = vec2(gl_FragCoord.xy+vec2(x,y));
    float yCoord = clamp(absCorrd.y,0.0,float(textureSize(tex,0).y));
    float xCoord = absCorrd.x;
    if(absCorrd.y>textureSize(tex,0).y||absCorrd.y < 0.0)
        xCoord= abs(textureSize(tex,0).x-abs(absCorrd.x));

    return texture2D(tex,fract(vec2(xCoord,yCoord)/ textureSize(tex,0))  ).xyz;
}

float getGround(float x, float y)
{
    return getTexValue(rock,x,y).x + getTexValue(soil,x,y).x;

}

float diffuse( float h1, float x, float y)
{

    float h2 = getTexValue(moist, x, y).x;

    float diff = (h2-h1)/8.0;
    return clamp(diff, -h1/2.0, h2/2.0);
}


void main() 
{
    float new_moist = 0.0;
    float temperature = getTexValue(temp,0.0,0.0).x;


    if(getTexValue(ice,0.0,0.0).x > 0.001)
    {
        new_moist = -0.003;
    }
   else if(getTexValue(water,0.0,0.0).x > 0.04) //if water is high enough
    {
         new_moist += 0.003 * waterAddFactor;
    }
    else
    {
        new_moist *= 0.4*mix(0.8,1.7,clamp(temperature,0.0,1.0)) ;
        new_moist -=  landRemoveFactor*0.001;
    }

    new_moist =  (getTexValue(moist, 0, 0).x+new_moist) ;




  float tf = 0.4;
    float tm = 0.4;

    vec3 w = getTexValue(wind, 0.0, 0.0);
    vec3 g = getTexValue(moist, 0.0, 0.0);

    vec3 w_left    = getTexValue(wind, -1.0,  0.0);
    vec3 w_right   = getTexValue(wind,  1.0,  0.0);
    vec3 w_top     = getTexValue(wind,  0.0,  1.0);
    vec3 w_bot     = getTexValue(wind,  0.0, -1.0);

    vec3 g_left    = getTexValue(moist, -1.0,  0.0);
    vec3 g_right   = getTexValue(moist,  1.0,  0.0);
    vec3 g_top     = getTexValue(moist,  0.0,  1.0);
    vec3 g_bot     = getTexValue(moist,  0.0, -1.0);
    //change temperature based on wind direction
    float moist_transported_off = (min(abs(tf*w.x), tm) + min(abs(w.y*tf), tm))*g.x;

    float moist_transported_in = (
        clamp(w_left.x*tf, 0.0, tm) * g_left.x +
        clamp(-w_right.x*tf, 0.0, tm) * g_right.x +
       clamp(-w_top.y*tf, 0.0, tm) * g_top.x +
        clamp(w_bot.y*tf, 0.0, tm) * g_bot.x
    );
   new_moist += (moist_transported_in ) - moist_transported_off;


  new_moist = new_moist  + diffuse(new_moist, 0.0, 1.0) + diffuse(new_moist, 0.0, -1.0) ;
   new_moist = new_moist + diffuse(new_moist, 1.0, 0.0) + diffuse(new_moist, - 1.0, 0.0) ;




    new_moist = clamp(new_moist, 0.0, 1.0 );
 
    color = vec3(new_moist,0.0,0.0);
}
