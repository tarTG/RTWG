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

uniform mat4 depthMVP; //model view matrix
uniform mat4 model_matrix;



in vec2 texCoordT[];
out vec2 texcoordF;


uniform ivec2 dimensions;

float height(float u, float v) 
{
	return texture(rock, vec2(u,v)).x + texture(soil , vec2(u,v)).x+ texture(water , vec2(u,v)).x;// + texture(ice , vec2(u,v)).x);
}


void main()
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

     vec3    p0 = gl_in[0].gl_Position.xyz;
    vec3 p1 =gl_in[1].gl_Position.xyz ;
    vec3 p2 =gl_in[2].gl_Position.xyz;
    vec3 p3 = gl_in[3].gl_Position.xyz;


    vec2 t1 = mix(texCoordT[0], texCoordT[1], u);
    vec2 t2 = mix(texCoordT[2], texCoordT[3], u);
    texcoordF = mix(t2, t1, v);        

    vec3 p_1 = mix(p0 , p1, u);
    vec3 p_2 = mix(p2, p3, u);

    vec3 q =mix(p_2, p_1, v) ;
    q.y = texture(rock,texcoordF).x;  


 
    gl_Position  = (depthMVP *model_matrix ) * vec4(q,1.0) ;


}
        