#version 420 core

//incoming tesselated primitives
layout (quads) in;
//height texture
layout (binding = 0) uniform sampler2D rock;
layout (binding = 1) uniform sampler2D soil;
layout (binding = 2) uniform sampler2D water;
layout (binding = 3) uniform sampler2D temp;
layout (binding = 4) uniform sampler2D moist;
layout (binding = 5) uniform sampler2D wind;
layout (binding = 6) uniform sampler2D ice;
layout (binding = 7) uniform sampler2D mixtex;

uniform mat4 mv_matrix; //model view matrix
uniform mat4 proj_matrix; //projection matrix
uniform vec3 light_pos = vec3(0.0, 0.0,0.0);
uniform mat4 model_matrix;
uniform mat4 shadowMVP;

uniform float heightFactor = 1.0;

in vec2 texCoordT[];
out vec2 texcoordF;

out vec4 shadowCoord;

out VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} vs_out;


uniform ivec2 dimensions;

float height(vec2 coord) 
{
	return texture(rock, coord).x + texture(soil , coord).x;
}

vec3 calcNormal (vec2 tCoord, vec2 dist)
{
    vec2 p = 1.0/textureSize(rock,0);
    vec3 v1 = vec3(0.0, height(tCoord + (p*vec2(0.0,-1.0))) * heightFactor, p.y*-1.0);
    vec3 v2 = vec3(p.x*1.0, height(tCoord + (p*vec2(1.0,0.0))) * heightFactor, 0.0);
    vec3 v3 = vec3(0.0, height(tCoord + (p*vec2(0.0,1.0)))  * heightFactor, p.y*1.0);
    vec3 v4 = vec3(p.x*-1.0, height(tCoord + (p*vec2(-1.0,0.0))) * heightFactor, 0.0);
    return normalize(normalize(cross(v1,v2))+normalize(cross(v2,v3))+normalize(cross(v3,v4))+normalize(cross(v4,v1)));
            
}








void main()
{

    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    vec3 p0 = gl_in[0].gl_Position.xyz ;
    vec3 p1 =gl_in[1].gl_Position.xyz ;
    vec3 p2 =gl_in[2].gl_Position.xyz;
    vec3 p3 = gl_in[3].gl_Position.xyz ;


    vec2 dist = gl_in[0].gl_Position.xz-gl_in[1].gl_Position.xz;

    vec2 t1 = mix(texCoordT[0], texCoordT[1], u);
    vec2 t2 = mix(texCoordT[2], texCoordT[3], u);
    texcoordF = mix(t2, t1, v);        

    vec3 p_1 = mix(p0 , p1, u);
    vec3 p_2 = mix(p2, p3, u);

    vec3 q =mix(p_2, p_1, v) ;
   q.y = height( texcoordF) * heightFactor;  

    shadowCoord =     (shadowMVP *model_matrix)   * vec4(q,1.0) ;
 
    gl_Position  = proj_matrix * mv_matrix  * vec4(q,1.0) ;
    vec4 pos = model_matrix  *vec4(q,1.0);


   vec4 Nposition = model_matrix  *vec4(q,1.0);

    vec3 lpos = vec3(dimensions.x*0.5,0.0,dimensions.y*0.5) - light_pos;
    vs_out.N = transpose(inverse(mat3(model_matrix))) *  calcNormal(texcoordF,dist);
    vs_out.L = lpos - ((Nposition.xyz)/Nposition.w);
    vs_out.V = -((Nposition.xyz)/Nposition.w);
    

}
        