#version 420 core


in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} vs_out; 


in vec2 texcoordF;

layout (binding = 0) uniform sampler2D rock;
layout (binding = 1) uniform sampler2D soil;
layout (binding = 2) uniform sampler2D water;
layout (binding = 3) uniform sampler2D temp;
layout (binding = 4) uniform sampler2D moist;
layout (binding = 5) uniform sampler2D wind;
layout (binding = 6) uniform sampler2D ice;
layout (binding = 7) uniform sampler2D mixtex;
layout (binding = 8) uniform sampler2DShadow shadow_tex;

layout (binding = 9) uniform sampler2DArray texArray;



const uint texIndexDirt                     = 0;
const uint texIndexBeachSand                     = 1;
const uint texIndexforestWarm                     = 2;
const uint texIndexRock                    = 3;
const uint texIndexrainForest                     = 4;
const uint texIndexDesert                     = 5;
const uint texIndexSnow                     = 6;
const uint texIndextundraCold                     = 7;
const uint texIndextundraWet                     = 8;
const uint texIndexWater                     = 9;

uniform uint currentSelection = 7;

vec3 getTexValue(sampler2D tex, float x, float y)
{
   // return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;

     return texture(tex,texcoordF).xyz;
}

vec3 getTexValue(sampler2DArray tex,uint layer, float x, float y)
{
   // return texture2D(tex, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(tex,0))).xyz;

     return texture(tex,vec3(fract(texcoordF*10),layer)).xyz;
}

vec3 calcTextureColor()
{
    vec3 color;
const vec3 Color_Polar_desert                     = vec3(1.0,1.0,1.0);
const vec3 Color_Subpolar_dry_tundra              = vec3(0.5,0.5,0.5);
const vec3 Color_Subpolar_moist_tundra            = vec3(0.38,0.5,0.5);
const vec3 Color_Subpolar_wet_tundra              = vec3(0.25,0.5,0.5);
const vec3 Color_Subpolar_rain_tundra             = vec3(0.125,0.5,0.75);
const vec3 Color_Boreal_desert                    = vec3(0.62,0.62,0.5);
const vec3 Color_Boreal_dry_scrub                 = vec3(0.5,0.62,0.62);
const vec3 Color_Boreal_moist_forest              = vec3(0.37,0.62,0.5);
const vec3 Color_Boreal_wet_forest                = vec3(0.25,0.62,0.56);
const vec3 Color_Boreal_rain_forest               = vec3(0.125,0.62,0.75);
const vec3 Color_Cool_temperate_desert            = vec3(0.75,0.75,0.5);
const vec3 Color_Cool_temperate_desert_scrub      = vec3(0.62,0.75,0.5);
const vec3 Color_Cool_temperate_steppe            = vec3(0.5,0.75,0.5); 
const vec3 Color_Cool_temperate_moist_forest      = vec3(0.37,0.75,0.5);
const vec3 Color_Cool_temperate_wet_forest        = vec3(0.25,0.75,0.56);
const vec3 Color_Cool_temperate_rain_forest       = vec3(0.125,0.75,0.75);
const vec3 Color_Warm_temperate_desert            = vec3(0.87,0.8,0.5);
const vec3 Color_Warm_temperate_desert_scrub      = vec3(0.81,0.8,0.5);
const vec3 Color_Warm_temperate_thorn_scrub       = vec3(0.62,0.8,0.5);
const vec3 Color_Warm_temperate_dry_forest        = vec3(0.5,0.8,0.5);
const vec3 Color_Warm_temperate_moist_forest      = vec3(0.37,0.8,0.5);
const vec3 Color_Warm_temperate_wet_forest        = vec3(0.25,0.8,0.56);
const vec3 Color_Warm_temperate_rain_forest       = vec3(0.125,0.8,0.75);
const vec3 Color_Subtropical_desert               = vec3(0.92,0.95,0.5);
const vec3 Color_Subtropical_desert_scrub         = vec3(0.82,0.95,0.5);
const vec3 Color_Subtropical_thorn_woodland       = vec3(0.69,0.95,0.5);
const vec3 Color_Subtropical_dry_forest           = vec3(0.5,0.95,0.5);
const vec3 Color_Subtropical_moist_forest         = vec3(0.37,0.95,0.5);
const vec3 Color_Subtropical_wet_forest           = vec3(0.25,0.95,0.56);
const vec3 Color_Subtropical_rain_forest          = vec3(0.125,0.95,0.69);
const vec3 Color_Tropical_desert                  = vec3(1.0,1.0,0.5);
const vec3 Color_Tropical_desert_scrub            = vec3(0.88,1.0,0.5);
const vec3 Color_Tropical_thorn_woodland          = vec3(0.75,1.0,0.5);
const vec3 Color_Tropical_very_dry_forest         = vec3(0.63,1.0,0.5);
const vec3 Color_Tropical_dry_forest              = vec3(0.5,1.0,0.5);
const vec3 Color_Tropical_moist_forest            = vec3(0.37,1.0,0.5);
const vec3 Color_Tropical_wet_forest              = vec3(0.25,1.0,0.56);
const vec3 Color_Tropical_rain_forest             = vec3(0.125,1.0,0.62);
const vec3 Color_Ocean                            = vec3(0.0,0.0,0.5);
const vec3 Color_River                            = vec3(0.0,0.4,0.8);
const vec3 Color_Sand                             = vec3(0.0,0.0,0.0);
const vec3 Color_Rock                             = vec3(0.0,0.0,0.0);
const vec3 Color_Lake                             = vec3(0.0,0.0,0.7);

        
   /* float tempZone = getTexValue(mixtex,0.0,0.0).y
    if(tempZone == 0.5)
        //subpolar
    else if(tempZone==0.62)
        //boreal
    else if(tempZone==0.75)
        //cool        
    else if(tempZone==0.8)
        //warm        
    else if(tempZone==0.95)
        //subtropical
    else
        //tropicla*/
    color = getTexValue(mixtex,0.0,0.0);;
    color = mix(color,getTexValue(texArray,texIndexSnow,0.0,0.0),getTexValue(ice,0.0,0.0).x);
    //color = mix(color,getTexValue(texArray,texIndexWater,0.0,0.0),getTexValue(water,0.0,0.0).x);
    color = mix(color,getTexValue(texArray,texIndexDirt,0.0,0.0),getTexValue(soil,0.0,0.0).x);

    return color;
}





in vec4 shadowCoord;
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

                 color  = vec3(abs(getTexValue(water,0.0,0.0).xyz));

                break;
            case 3:
                color = getTexValue(temp,0.0,0.0).xyz;
                break;
            case 4:
                color = vec3(getTexValue(moist,0.0,0.0).x,0.0,0.0);
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
            case 8:
                color = calcTextureColor();
                break;
        }



    if( currentSelection == 8)   
    {
    vec3 N = normalize(vs_out.N);
    vec3  L = normalize(vs_out.L);
    vec3 V = normalize(vs_out.V);


    vec4 v_diffuse = max(dot(N,L), 0.0) * vec4(0.3,0.3,0.0,0.0);
    vec4 v_specular= vec4(0.0,0.0,0.0,0.0);
    if(dot(N,L) < 0.0)
    {
    }  
    else
    {

        v_specular = pow(max(dot(reflect(-L,N),V),0.0), 0.99) * vec4(0.7);
        
    }
    float visibility = 0.0;
          vec3 sCoord = shadowCoord.xyz/ shadowCoord.w;


    if(shadowCoord.w <= 0.f || (sCoord.x < 0 || sCoord.y < 0) || (sCoord.x >= 1 || sCoord.y >= 1))
    {
        visibility = 1.0;
    }
    else
    {
        visibility += textureProjOffset(shadow_tex,vec4(sCoord,1.0),ivec2(1,1)).x;
          visibility += textureProjOffset(shadow_tex,vec4(sCoord,1.0),ivec2(1,-1)).x;  
           visibility += textureProjOffset(shadow_tex,vec4(sCoord,1.0),ivec2(-1,1)).x;
        visibility += textureProjOffset(shadow_tex,vec4(sCoord,1.0),ivec2(-1,-1)).x;     
                  visibility /= 4.0;
    }
    color =    (visibility *v_diffuse.xyz) + 0.6*color;//(texture2D(shadow_tex, (shadowCoord.xy)/textureSize(shadow_tex,0)).z ) ;
    }
}


