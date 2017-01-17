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


layout (binding = 8) uniform sampler2D noiseTex;

uniform float distorsionFaktor = 1.0;
uniform float globelWindFaktor = 1.0;
uniform float localPressureFaktor = 1.0;
uniform float timeFactorWind = 0.0;
uniform float windspeed = 0.0;

out vec3 color;



float getNoiseValue(vec2 coord)
{
    return (texture2D(noiseTex,((gl_FragCoord.xy )/textureSize(noiseTex,0)+coord)+vec2(sign((gl_FragCoord.y/textureSize(noiseTex,0).y)-0.5)*(timeFactorWind*0.001),0.0)).x * 2) -1;
}

vec3 getTexValue(sampler2D tex, float x, float y)
{
    return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;
}

float getGround(float x, float y)
{
    return getTexValue(rock,x,y).x + getTexValue(soil,x,y).x;
}


float calculatePressure(vec2 dir)
{
    float pressure = (-getTexValue(temp,dir.x, dir.y).x +1.0) + 1.0-( getTexValue(moist,dir.x, dir.y).x ) ;
    pressure = 1/(getGround(dir.x, dir.y).x  + getTexValue(water,dir.x, dir.y).x) *10;
    
    return pressure;
}

vec2 getWindDirection(vec2 dir, float curPressure, float dirPressure)
{
    return dir * ( dirPressure-curPressure) ;
}

float getGlobalWindDirectionX()
{
    float latitude = (gl_FragCoord.xy/textureSize(wind,0)).y +0.1;

    return clamp((-(cos(latitude*11))* globelWindFaktor)+(getNoiseValue(vec2(0.5))*distorsionFaktor),-1.0,1.0);
        
}

float getGlobalWindDirectionY()
{
    float latitude = fract((gl_FragCoord.xy/textureSize(rock,0)).y );
     
     float ret = clamp((-cos(latitude*PI*3)* globelWindFaktor)+(getNoiseValue(vec2(0.0))*distorsionFaktor),-1.0,1.0);

     return ret;
}


vec3 diffuse( vec3 h1, float x, float y)
{

    vec3 h2 = getTexValue(wind, x, y);

    vec3 diff = (h2-h1) /4.0;
    return diff;
}



void main() 
{
    vec2 top = vec2(0,1), bot = vec2(0,-1), left = vec2(-1,0), right = vec2(1,0), current= vec2(0,0);

    
    vec2 windDirection;
    float pressure = calculatePressure(current) ;

     windDirection.y = (getWindDirection(top,pressure,getTexValue(wind,top.x , top.y).z).y + getWindDirection(bot,pressure,getTexValue(wind,bot.x , bot.y).z).y)  ;
    windDirection.x = (getWindDirection(left,pressure,getTexValue(wind,left.x , left.y).z).x + getWindDirection(right,pressure,getTexValue(wind,right.x , right.y).z).x);
    
    windDirection *= localPressureFaktor;
    //-temp , -altitude, -moist


    windDirection.xy += (
        getTexValue(wind,-1.0, 1.0).xy*1.0    + getTexValue(wind,0.0, 1.0).xy*1.4    + getTexValue(wind,1.0, 1.0).xy*1.0 +
        getTexValue(wind,-1.0,  0.0).xy*1.4     +windDirection.xy*400.0              +         getTexValue(wind,1.0, 0.0).xy*1.4 +
        getTexValue(wind,-1.0, -1.0).xy*1.0    + getTexValue(wind,0.0, -1.0).xy*1.4    + getTexValue(wind,1.0, -1.0).xy*1.0
   )/(400.0+1.4*4.0+4.0);

   windDirection= vec2(getGlobalWindDirectionX(),getGlobalWindDirectionY()) + windDirection ;

    
    vec3 ret = vec3(windDirection,-pressure);
    ret +=( diffuse(ret, 0.0, 1.0) + diffuse(ret, 0.0, -1.0)) ;
    ret += (diffuse(ret, 1.0, 0.0) + diffuse(ret, - 1.0, 0.0))  ;

    ret.xy = clamp(ret.xy ,-1.0,1.0);

    color = ret;//
  
}
