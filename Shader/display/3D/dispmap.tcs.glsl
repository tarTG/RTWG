#version 420 core


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

in vec2 texCoord[];
out vec2 texCoordT[];
// Inputs from vertex shader





layout(vertices = 4) out;

uniform vec2 screen_size = vec2(800,600);;
uniform float lod_factor = 4.0;
    
bool segmentInFrustum(vec4 p1, vec4 p2) {

	if ((p1.x < -p1.w && p2.x < -p2.w) || (p1.x > p1.w && p2.x > p2.w) ||
	//	(p1.y < -p1.w && p2.y < -p2.w) || (p1.y > p1.w && p2.y > p2.w) ||
		(p1.z < -p1.w && p2.z < -p2.w) || (p1.z > p1.w && p2.z > p2.w))
		return true;
	else
		return false;

}

    vec2 screen_space(vec4 vertex){
        return (clamp(vertex.xy, -1.3, 1.3)+1) * (screen_size*0.5);
    }

    float level(vec2 v0, vec2 v1){
        return clamp(distance(v0, v1)/lod_factor, 1, 64);
    }

    void main()
{
             if(gl_InvocationID == 0)
        {
            vec4 v0 = proj_matrix * mv_matrix * gl_in[0].gl_Position;
            vec4 v1 = proj_matrix * mv_matrix * gl_in[1].gl_Position;
            vec4 v2 = proj_matrix * mv_matrix *gl_in[2].gl_Position;
            vec4 v3 = proj_matrix * mv_matrix *gl_in[3].gl_Position;

            v0 /= v0.w;
            v1 /= v1.w;
            v2 /= v2.w;
            v3 /= v3.w;


       if(all(bvec4(segmentInFrustum(v0,v1), segmentInFrustum(v0,v2), segmentInFrustum(v2,v3),segmentInFrustum(v3,v1)))){
                gl_TessLevelInner[0] = 0;
                gl_TessLevelInner[1] = 0;
                gl_TessLevelOuter[0] = 0;
                gl_TessLevelOuter[1] = 0;
                gl_TessLevelOuter[2] = 0;
                gl_TessLevelOuter[3] = 0;
            }
            else{
            float l0 = length(v0.xy - v1.xy)*7+1;
            float l1 = length(v0.xy - v2.xy)*7 +1;
            float l2 = length(v2.xy - v3.xy)*7 +1;
            float l3 = length(v3.xy - v1.xy)*7 +1;


           /*     gl_TessLevelInner[0] = mix(l0, l1, 0.5);
                gl_TessLevelInner[1] = mix(l2, l3, 0.5);
                gl_TessLevelOuter[0] = l0;
                gl_TessLevelOuter[1] = l1;
                gl_TessLevelOuter[2] = l2;
                gl_TessLevelOuter[3] = l3;*/
                gl_TessLevelInner[0] = 15;
                gl_TessLevelInner[1] = 15;
                gl_TessLevelOuter[0] = 15;
                gl_TessLevelOuter[1] = 15;
                gl_TessLevelOuter[2] = 15;
                gl_TessLevelOuter[3] = 15;
            }
        }

	texCoordT[gl_InvocationID] = texCoord[gl_InvocationID];
        gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;  

}
