#version 420 core


in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} vs_out; 

#define PI 3.14159265358979323846

in vec2 texcoordF;
in vec2 tessCoord;
layout (binding = 0) uniform sampler2D rock;
layout (binding = 1) uniform sampler2D soil;
layout (binding = 2) uniform sampler2D water;
layout (binding = 3) uniform sampler2D temp;
layout (binding = 4) uniform sampler2D moist;
layout (binding = 5) uniform sampler2D wind;
layout (binding = 6) uniform sampler2D ice;
layout (binding = 7) uniform sampler2D mixtex;
layout (binding = 8) uniform sampler2DShadow shadow_tex;

layout (binding = 9) uniform sampler2D waterNormals;
layout (binding = 11) uniform sampler2D waterFlow;

uniform ivec2 dimensions;
uniform float waterSpeed;

in vec4 position;

vec3 getTexValue(sampler2D tex, float x, float y)
{

     return texture(tex,texcoordF+ (vec2(x,y)/textureSize(tex,0))).xyz;
}


vec3 getnormal()
{


    vec2 mid= getTexValue(waterFlow, 0,0).xy*-waterSpeed;
   vec2 down = (getTexValue(waterFlow, -1,1).xy*-waterSpeed+mid)*0.5;
    vec2 top = (getTexValue(waterFlow, 1, 1).xy*-waterSpeed+mid)*0.5;
    vec2 right = (getTexValue(waterFlow, -1, -1).xy*-waterSpeed+mid)*0.5;
    vec2 left = (getTexValue(waterFlow,1,-1 ).xy*-waterSpeed+mid)*0.5;
            
 
    
 vec3 downt = normalize(texture2D(waterNormals,(texcoordF+(vec2(-1,1)/textureSize(waterFlow,0)))*400+down).xyz*2-1);
    vec3 topt = normalize(texture2D(waterNormals,(texcoordF+(vec2(1,1)/textureSize(waterFlow,0)))*400+top).xyz*2-1);
    vec3 rightt = normalize(texture2D(waterNormals,(texcoordF+(vec2(-1,-1)/textureSize(waterFlow,0)))*400+right).xyz*2-1);
    vec3 leftt = normalize(texture2D(waterNormals,(texcoordF+(vec2(1,-1)/textureSize(waterFlow,0)))*400+left).xyz*2-1);

 vec3 normal1 = mix(downt, topt,tessCoord.x);
    vec3 normal2 = mix(rightt, leftt, tessCoord.x);
    vec3 normal = mix(normal2,normal1,tessCoord.y);
   return normalize(normal);
}


in vec4 shadowCoord;
out vec4 color;

void main() 
{

    vec3 w = getTexValue(water, 0, 0);



    float speed_factor = clamp(length(w.yz)/0.02, 0.0, 1.0);
    float depth_factor = clamp(w.x/0.01, 0.0, 1.0);

    vec3 deep = vec3(0.0, 51.0/255.0, 128.0/255.0)*0.5;
    vec3 flatw = vec3(0.0/255.0, 100.0/255.0, 130.0/255.0)*0.7;

    vec3 tcolor = mix(flatw, deep, sqrt(clamp(w.x/0.0075, 0.0, 1.0)));

    vec3 base_normal = normalize(vs_out.N);
    vec3 tangent = normalize(cross(base_normal, vec3(0.0, 0.0, 1.0)));
    vec3 bitangent = normalize(cross(tangent, base_normal));
    mat3 orthobasis = mat3(tangent, base_normal, bitangent);
    vec3 detail_normal = orthobasis * getnormal();
    vec3 normal = normalize(mix(base_normal*0.5+detail_normal*0.5, detail_normal, speed_factor));
    normal = normalize(mix(normal, base_normal, sqrt(clamp(w.x/0.0075, 0.0, 1.0))*0.75));

    vec3 N =normal;
    vec3  L = normalize(vs_out.L);
    vec3 V = normalize(vs_out.V);


    vec3 v_diffuse = max(dot(N,L), 0.0) * vec3(0.0, 90.0/255.0, 120.0/255.0);
    vec3 v_specular= vec3(0.00,0.0,0.0);
    float spec;
    if(dot(N,L) >= 0.0)
    {
            v_specular = pow(max(dot(reflect(-L,N),V),0.0), 0.5) * vec3(0.5,0.5, 0.8);
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

        color =vec4((v_diffuse.xyz + tcolor +v_specular) *visibility,depth_factor) ;


    if(w.x <0.04 && length(w.yz) < 0.02)
        color = mix(vec4(0.0),vec4(color.xyz,1.0),(w.x+length(w.yz))*40) ;;
}


