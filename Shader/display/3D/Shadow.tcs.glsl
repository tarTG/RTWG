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

uniform mat4 depthMVP; //model view matrix
uniform mat4 model_matrix;

in vec2 texCoord[];
out vec2 texCoordT[];
// Inputs from vertex shader


layout(vertices = 4) out;

    
bool segmentInFrustum(vec4 p1, vec4 p2) {

	if ((p1.x < -p1.w && p2.x < -p2.w) || (p1.x > p1.w && p2.x > p2.w) ||
	//	(p1.y < -p1.w && p2.y < -p2.w) || (p1.y > p1.w && p2.y > p2.w) ||
		(p1.z < -p1.w && p2.z < -p2.w) || (p1.z > p1.w && p2.z > p2.w))
		return true;
	else
		return false;

}


    void main()
{
          if(gl_InvocationID == 0)
        {
            vec4 v0 = depthMVP *model_matrix* gl_in[0].gl_Position;
            vec4 v1 = depthMVP * model_matrix*gl_in[1].gl_Position;
            vec4 v2 = depthMVP *model_matrix*gl_in[2].gl_Position;
            vec4 v3 = depthMVP *model_matrix*gl_in[3].gl_Position;
 
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

                gl_TessLevelInner[0] = 10;
                gl_TessLevelInner[1] = 10;
                gl_TessLevelOuter[0] = 10;
                gl_TessLevelOuter[1] = 10;
                gl_TessLevelOuter[2] = 10;
                gl_TessLevelOuter[3] = 10;
            
     }
        }

	texCoordT[gl_InvocationID] = texCoord[gl_InvocationID];
        gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;  

}
