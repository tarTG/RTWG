/*
 * Sample dummy shader to check the highlighter plugin.
 */

#version 430 core


layout (binding = 0) uniform sampler2D tex;
/*layout (binding = 1) uniform sampler2D soil;
layout (binding = 2) uniform sampler2D water;
layout (binding = 3) uniform sampler2D temp;
layout (binding = 4) uniform sampler2D moist;
layout (binding = 5) uniform sampler2D wind;
layout (binding = 6) uniform sampler2D ice;
layout (binding = 7) uniform sampler2D mixtex;
layout (binding = 8) uniform sampler2D shadow;*/


uniform uint currentSelection = 7;
uniform ivec2 WindowDimension = ivec2(800,600);

vec3 getTexValue(sampler2D tex, float x, float y)
{
   // return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;
    vec2 div = textureSize(tex,0)/vec2(WindowDimension);
    return texture(tex, (div*gl_FragCoord.xy)/(textureSize(tex,0))).xyz;
}


vec3 renderHeightMap(float c)
{
    const float COLOR_STEP=	1.0f;
    vec3 color = vec3(0.0);
    if (c < 0.5)
        color = vec3(0.0, 0.0, 0.25 + 1.5 * c);
    else if (c < 1.0)
        color = vec3(0.0, 2 * (c - 0.5), 1.0);
    else
    {
      c -= 1.0;
      if (c < 1.0 * COLOR_STEP)
           color = vec3(0.0, 0.5 + 0.5 * c / COLOR_STEP, 0.0);
      else if (c < 1.5 * COLOR_STEP)
           color = vec3(2 * (c - 1.0 * COLOR_STEP) / COLOR_STEP, 1.0, 0.0);
      else if (c < 2.0 * COLOR_STEP)
           color = vec3(1.0, 1.0 -(c - 1.5 * COLOR_STEP)/COLOR_STEP, 0);
      else if (c < 3.0 * COLOR_STEP)
           color = vec3(1.0 - 0.5 * (c - 2.0 * COLOR_STEP) / COLOR_STEP, 
                        0.5 - 0.25 * (c - 2.0 * COLOR_STEP) / COLOR_STEP, 
                        0);
      else if (c < 5.0 * COLOR_STEP)
           color = vec3(0.5 - 0.125 * (c - 3.0 *  COLOR_STEP) / (2*COLOR_STEP),
                    0.25 + 0.125 * (c - 3.0 * COLOR_STEP) / (2*COLOR_STEP),
                    0.375 * (c - 3.0 *  COLOR_STEP) / (2*COLOR_STEP));
      else if (c < 8.0 * COLOR_STEP)
           color = vec3(0.375 + 0.625 * (c - 5.0 * COLOR_STEP) / (3*COLOR_STEP),
                    0.375 + 0.625 * (c - 5.0 * COLOR_STEP) / (3*COLOR_STEP),
                    0.375 + 0.625 * (c - 5.0 * COLOR_STEP) / (3*COLOR_STEP));
      else
      {
            c -= 8.0 * COLOR_STEP;
            while (c > 2.0 * COLOR_STEP)
                    c -= 2.0 * COLOR_STEP;

            color = vec3(1, 1 , 1);
        }
    }
    return color;
}



out vec3 color;

void main() 
{

        switch(currentSelection)
        {
            case 0:
                color = renderHeightMap(getTexValue(tex,0.0,0.0).x);
                break;
            case 1:
                color = getTexValue(tex,0.0,0.0).xyz*10;
                break;
            case 2:
                color = abs(getTexValue(tex,0.0,0.0).xyz)*5;
                // color  = vec3(length(getTexValue(water,0.0,0.0).yz),0.0,0.0);
                break;
            case 3:
                color = getTexValue(tex,0.0,0.0).xyz;
                break;
            case 4:
                color = getTexValue(tex,0.0,0.0).xxx;
                break;
            case 5:
                color = getTexValue(tex,0.0,0.0).xyz;
                break;
            case 6:
                color = getTexValue(tex,0.0,0.0).xyz;
                break;
            case 7:
                color = getTexValue(tex,0.0,0.0).xyz;
                break;
        }




 
}
