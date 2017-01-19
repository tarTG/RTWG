
#version 430 core

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
const vec3 Color_Ocean                            = vec3(0.0,0.0,0.4);
const vec3 Color_River                            = vec3(0.0,0.4,0.8);
const vec3 Color_Sand                             = vec3(0.0,0.0,0.0);
const vec3 Color_Rock                             = vec3(0.0,0.0,0.0);
const vec3 Color_Lake                             = vec3(0.0,0.0,0.8);


const uint  alpine = 1;
const uint  boreal = 2;
const uint  cool = 3;
const uint  warm = 4;
const uint  subtropical = 5;
const uint  tropical = 6;

const uint  superarid = 1;
const uint  perarid = 2;
const uint  arid = 3;
const uint  semiarid = 4;
const uint  subhumid = 5;
const uint  humid = 6;
const uint  perhumid = 7;
const uint  superhumid = 8;


const float temp_alpine     = -0.8;
const float temp_boreal     = -0.3;
const float temp_cool       = 0.0;
const float temp_warm       = 0.25;
const float temp_subtropical= 0.5;
const float temp_tropical   = 0.8;

const float humidity_superarid  = 0.1;
const float humidity_perarid    = 0.25;
const float humidity_arid       = 0.35;
const float humidity_semiarid   = 0.5;
const float humidity_subhumid   = 0.6;
const float humidity_humid      = 0.75;
const float humidity_perhumid   = 0.8;
const float humidity_superhumid = 1.0;
 
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
    return texture2D(rock, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(rock,0))).x
           + texture2D(soil, fract((gl_FragCoord.xy+vec2(x,y))/textureSize(soil,0))).x;
}


uint getHumidityZone()
{
    float humidity = getTexValue(moist, 0.0,0.0).x;
    if(humidity <= humidity_superarid)
    { 
        return superarid;
    }
    if(humidity <= humidity_perarid)
    {
        return perarid;
    }
    if(humidity <= humidity_arid)
    {
        return arid;
    }
    if(humidity <= humidity_semiarid)
    {
        return semiarid;
    }
    if(humidity <= humidity_subhumid)
    {
        return subhumid;
    }
    if(humidity <= humidity_humid)
    {
        return humid;
    }
    if(humidity <= humidity_perhumid)
    {
        return perhumid;
    }
    return superhumid;
}

uint getTemperatureZone()
{
    float temperature = getTexValue(temp, 0.0,0.0).x;
    if(temperature <= temp_alpine)
    { 
        return alpine;
    }
    if(temperature <= temp_boreal)
    {
        return boreal;
    }
    if(temperature <= temp_cool)
    {
        return cool;
    }
    if(temperature <= temp_warm)
    {
        return warm;
    }
    if(temperature <= temp_subtropical)
    {
        return subtropical;
    }
    return tropical;
}




void main() 
{
    vec3 value ;
    if(getTexValue(ice, 0.0,0.0).x > 0.1)
    {
        value = Color_Polar_desert;
    }

    else if(getTexValue(water, 0.0,0.0).x > 0.1)
    {
        if(getGround(0.0,0.0) < 0.2)
        {
            value = Color_Ocean;
        
        }

        else
        {
            value = Color_Lake;
        }
    }
    else if(abs(getTexValue(water, 0.0,0.0).y) > 0.005 || abs(getTexValue(water, 0.0,0.0).z) > 0.005) 
    {
        value = Color_River;
    }
    else
    {
        uint tempZone = getTemperatureZone();
        uint humidZone = getHumidityZone();
        switch(tempZone)
        {
           case alpine:
           {
                switch(humidZone)
                {
                    case superarid:
                    {
                        value = Color_Subpolar_dry_tundra;
                        break;
                    }
                    case perarid:
                    {
                        value = Color_Subpolar_moist_tundra;
                        break;
                    }
                    case arid:
                    {
                        value = Color_Subpolar_wet_tundra;
                        break;
                    }
                    default:
                    {
                        value = Color_Subpolar_rain_tundra;
                        break;
                    }
                }
                break;
           }
           case boreal:
           {
                switch(humidZone)
                {
                    case superarid:
                    {
                        value = Color_Boreal_desert;
                        break;
                    }
                    case perarid:
                    {
                        value = Color_Boreal_dry_scrub;
                        break;
                    }
                    case arid:
                    {
                        value = Color_Boreal_moist_forest;
                        break;
                    }
                    case semiarid:
                    {
                        value = Color_Boreal_wet_forest;
                        break;
                    }
                    default:
                    {
                        value = Color_Boreal_rain_forest;
                        break;
                    }
                }
                break;
           }

           case cool:
           {
                switch(humidZone)
                {
                    case superarid:
                    {
                        value = Color_Cool_temperate_desert;
                        break;
                    }
                    case perarid:
                    {
                        value = Color_Cool_temperate_desert_scrub;
                        break;
                    }
                    case arid:
                    {
                        value = Color_Cool_temperate_steppe;
                        break;
                    }
                    case semiarid:
                    {
                        value = Color_Cool_temperate_moist_forest;
                        break;
                    }
                    case subhumid:
                    {
                        value = Color_Cool_temperate_wet_forest;
                        break;
                    }
                    default:
                    {
                        value = Color_Cool_temperate_rain_forest;
                        break;
                    }
                }
                break;
           }
           case warm:
           {
                switch(humidZone)
                {
                    case superarid:
                    {
                        value = Color_Warm_temperate_desert;
                        break;
                    }
                    case perarid:
                    {
                        value = Color_Warm_temperate_desert_scrub;
                        break;
                    }
                    case arid:
                    {
                        value = Color_Warm_temperate_thorn_scrub;
                        break;
                    }
                    case semiarid:
                    {
                        value = Color_Warm_temperate_dry_forest;
                        break;
                    }
                    case subhumid:
                    {
                        value = Color_Warm_temperate_moist_forest;
                        break;
                    }
                    case humid:
                    {
                        value = Color_Warm_temperate_wet_forest;
                        break;
                    }
                    default:
                    {
                        value = Color_Warm_temperate_rain_forest;
                        break;
                    }
                }
                break;
           }
           case subtropical:
           {
                switch(humidZone)
                {
                    case superarid:
                    {
                        value = Color_Subtropical_desert;
                        break;
                    }
                    case perarid:
                    {
                        value = Color_Subtropical_desert_scrub;
                        break;
                    }
                    case arid:
                    {
                        value = Color_Subtropical_thorn_woodland;
                        break;
                    }
                    case semiarid:
                    {
                        value = Color_Subtropical_dry_forest;
                        break;
                    }
                    case subhumid:
                    {
                        value = Color_Subtropical_moist_forest;
                        break;
                    }
                    case humid:
                    {
                        value = Color_Subtropical_wet_forest;
                        break;
                    }
                    default:
                    {
                        value = Color_Subtropical_rain_forest;
                        break;
                    }
                }
                break;
           }
           case tropical:
           {
                switch(humidZone)
                {
                    case superarid:
                    {
                        value = Color_Tropical_desert;
                        break;
                    }
                    case perarid:
                    {
                        value = Color_Tropical_desert_scrub;
                        break;
                    }
                    case arid:
                    {
                        value = Color_Tropical_thorn_woodland;
                        break;
                    }
                    case semiarid:
                    {
                        value = Color_Tropical_very_dry_forest;
                        break;
                    }
                    case subhumid:
                    {
                        value = Color_Tropical_dry_forest;
                        break;
                    }
                    case humid:
                    {
                        value = Color_Tropical_moist_forest;
                        break;
                    }
                    case perhumid:
                    {
                        value = Color_Tropical_wet_forest;
                        break;
                    }
                    default:
                    {
                        value = Color_Tropical_rain_forest;
                        break;
                    }
                }
                break;
           }
           default:
           {
                if(getTexValue(soil,0.0,0.0).x >0.0)
                    value = Color_Sand;
                else
                    value = Color_Rock;
           }
        }
    }
    color = value;
}
