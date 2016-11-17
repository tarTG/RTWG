/*
 * Sample dummy shader to check the highlighter plugin.
 */

#version 430 core

uniform float rain, evaporate ;
uniform float sea_level = 0.8;

layout (binding = 0) uniform sampler2D rock;
layout (binding = 1) uniform sampler2D soil;
layout (binding = 2) uniform sampler2D water;
layout (binding = 3) uniform sampler2D temp;
layout (binding = 4) uniform sampler2D moist;
layout (binding = 5) uniform sampler2D wind;
layout (binding = 6) uniform sampler2D ice;

out vec3 color;


vec3 getTexValue(sampler2D tex, float x, float y)
{
    return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;
}

float getGround(float x, float y)
{
    return getTexValue(rock,x,y).x + getTexValue(soil,x,y).x;

}

    vec3 exchange(float g1, vec3 l1, vec3 c1, float x, float y)
    {
        float g2 = getGround( x, y);
        vec3 c2 = getTexValue(water, x, y).xyz;
        float change = (g2+c2.x) - (g1+l1.x);
        change = clamp(change*0.25, -c1.x*0.25, c2.x*0.25);
        return vec3(change, vec2(-x*change, -y*change));
    }


vec3 diffuse(float t1, float h1, vec2 off)
{
        float t2 = getGround(off.x,off.y);
        float h2 = getTexValue(water, off.x, off.y).x;
        float f1 = t1+h1;
        float f2 = t2+h2;
        float diff = (f2-f1)/2.0;
        diff = clamp(diff*0.65, -h1/2.0, h2/2.0);
        return vec3(diff, (-off)*diff);
}

void main(void)
{

    float ground = getGround(0, 0);
    float temperature = getTexValue(temp, 0, 0).x;
    vec3 result = getTexValue(water, 0, 0);



  
    //diffuse
   vec3 result1 =  diffuse(ground,result.x, vec2(0.0, 1.0)) + diffuse(ground,result.x, vec2(0.0, -1.0));
   vec3  result2 =  diffuse(ground,result.x, vec2(1.0, 0.0)) + diffuse(ground,result.x, vec2(- 1.0, 0.0));

    result += mix(result1,result2,0.5);

    vec3 last = getTexValue(water, 0, 0);
        //flows
       vec3 v = (
            exchange(ground, last,result,   1.0,  0.0) +
            exchange(ground, last,result,  -1.0,  0.0) +
            exchange(ground, last,result,  0.0,  1.0) +
            exchange(ground, last,result,  0.0, -1.0)
        )*vec3(0.25, 0.25, 0.25);

       result = result + v;


        result.x -= mix(0.0000,0.000007,evaporate*(temperature+2 ));
        result.x += mix(0.0000,0.000028, rain* getTexValue(moist, 0, 0).x);
        result.x += getTexValue(ice, 0.0, 0.0).y*0.01;
            


        //calcualte water movement based on movements around
         result.yz = (
            getTexValue(water,-1.0, 1.0).yz*1.0    + getTexValue(water,0.0, 1.0).yz*1.4    + getTexValue(water,1.0, 1.0).yz*1.0 +
            getTexValue(water,-1.0,  0.0).yz*1.4     + result.yz*300.0              +         getTexValue(water,1.0, 0.0).yz*1.4 +
            getTexValue(water,-1.0, -1.0).yz*1.0    + getTexValue(water,0.0, -1.0).yz*1.4    + getTexValue(water,1.0, -1.0).yz*1.0
        )*0.98*(1.0/(300.0+1.4*4.0+4.0));   
    

    result.yz = clamp(  result.yz,vec2(-1.0),vec2(1.0));
    result.x =  clamp(  result.x,sea_level -ground,10.0);



    color = result;
    
}
