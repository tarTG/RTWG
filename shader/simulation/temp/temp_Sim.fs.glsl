/*
 * Sample dummy shader to check the highlighter plugin.
 */

#version 430 core

#define PI 3.14159265358979323846

layout (binding = 0) uniform sampler2D rock;
layout (binding = 1) uniform sampler2D soil;
layout (binding = 2) uniform sampler2D water;
layout (binding = 3) uniform sampler2D temp;
layout (binding = 4) uniform sampler2D moist;
layout (binding = 5) uniform sampler2D wind;
layout (binding = 6) uniform sampler2D ice;

uniform float latFactor = 2.0;
uniform float sunAngle = 0.0;
uniform float waterCooldown = 1.0;
uniform float heightCooldown = 1.0;
uniform float timeFactor = 1.0;
uniform float rotationSpeed = 1.0;
uniform float DayNightFactor = 1.0;

out vec3 color;


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
  
    float h2 = getTexValue(temp, x, y).x;

    float diff = (h2-h1)/4.0;
    return diff;// clamp(diff, -h1/2.0, h2/2.0);
}

float getDayNightValue(float temperature)
{
    float x = gl_FragCoord.x/(textureSize(temp,0)).x * PI* 2 - (timeFactor*rotationSpeed);
    float sunlight = sin(PI* 0.5 * cos(x))*0.7 +0.5 ;
    if( (gl_FragCoord.y+ sunAngle)/textureSize(temp,0).y < sunlight)
        return temperature;

        return  0.5 *DayNightFactor;


}


void main()
{
    //set temp on latitude
    float latitude = (((gl_FragCoord.xy+vec2(0.0,sunAngle))/textureSize(temp,0)).y ) ;
    float temperature = clamp(cos(latitude*2*PI +PI  ) ,-1.0,1.0) + latFactor;
  
    temperature = getDayNightValue(temperature) ;
    float heigth = getGround(0.0,0.0);
    float waterheight = getTexValue(water,0.0,0.0).x;

    if(heigth > heightCooldown)
        temperature -= mix(0.0,3.0,heigth*0.4); 

       

                  
    if( getTexValue(water,0.0,0.0).x > 0.1)
         temperature = (temperature * 0.003)+ getTexValue(temp,0.0,0.0).x;
    else 
        temperature = (temperature * 0.006)+ getTexValue(temp,0.0,0.0).x;


    float tf = 0.5;
    float tm = 0.9;


    vec3 w = getTexValue(wind, 0.0, 0.0);
    vec3 g = getTexValue(temp, 0.0, 0.0);

    vec3 w_left    = getTexValue(wind, -1.0,  0.0);
    vec3 w_right   = getTexValue(wind,  1.0,  0.0);
    vec3 w_top     = getTexValue(wind,  0.0,  1.0);
    vec3 w_bot     = getTexValue(wind,  0.0, -1.0);

    vec3 g_left    = getTexValue(temp, -1.0,  0.0);
    vec3 g_right   = getTexValue(temp,  1.0,  0.0);
    vec3 g_top     = getTexValue(temp,  0.0,  1.0);
    vec3 g_bot     = getTexValue(temp,  0.0, -1.0);
    //change temperature based on wind direction
   float heat_transported_off = (min(abs(tf*w.x), tm) + min(abs(w.y*tf), tm))*g.x;

    float heat_transported_in = (
        clamp(w_left.x*tf, 0.0, tm) * g_left.x +
        clamp(-w_right.x*tf, 0.0, tm) * g_right.x +
        clamp(-w_top.y*tf, 0.0, tm) * g_top.x +
        clamp(w_bot.y*tf, 0.0, tm) * g_bot.x
    );
   temperature += (heat_transported_in - heat_transported_off ) ;


   temperature = temperature  + diffuse(temperature, 0.0, 1.0) + diffuse(temperature, 0.0, -1.0);
   temperature = temperature + diffuse(temperature, 1.0, 0.0) + diffuse(temperature, - 1.0, 0.0);

    temperature = clamp(temperature, -1.0,1.0);
    color = vec3(temperature,0.0,-temperature);
   
}
