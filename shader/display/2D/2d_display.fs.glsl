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
layout (binding = 7) uniform sampler2D mixtex;
layout (binding = 8) uniform sampler2D shadow;


uniform uint currentSelection = 7;
uniform ivec2 WindowDimension = ivec2(800,600);

vec3 getTexValue(sampler2D tex, float x, float y)
{
   // return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;
    vec2 div = textureSize(tex,0)/vec2(WindowDimension);
    return texture(tex, (div*gl_FragCoord.xy)/(textureSize(tex,0))).xyz;
}

out vec3 color;

void main() 
{

        switch(currentSelection)
        {
            case 0:
                color.x = getTexValue(rock,0.0,0.0).x ;
                color.y = getTexValue(rock,0.0,0.0).x -1.5;
                color.z = getTexValue(rock,0.0,0.0).x -3.0;
                break;
            case 1:
                color = getTexValue(soil,0.0,0.0).xyz*10;
                break;
            case 2:
                color = getTexValue(water,0.0,0.0).xyz*2;
                // color  = vec3(length(getTexValue(water,0.0,0.0).yz),0.0,0.0);
                break;
            case 3:
                color = getTexValue(temp,0.0,0.0).xyz;
                break;
            case 4:
                color = getTexValue(moist,0.0,0.0).xxx;
                break;
            case 5:
                color = getTexValue(wind,0.0,0.0).xyz;
                break;
            case 6:
                color = getTexValue(ice,0.0,0.0).xyz;
                break;
            case 7:
                color = getTexValue(mixtex,0.0,0.0).xyz;
                break;
        }




 
}
