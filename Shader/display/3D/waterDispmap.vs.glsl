#version 420 core

//outgoing tesselation coordinates
in vec4 position;   
out vec2 texCoord;


uniform mat4 mv_matrix;    
uniform mat4 proj_matrix;
 
uniform ivec2 dimensions;






void main(void)
{  
        texCoord = (position.xz+vec2(0.5))/vec2(dimensions);
        gl_Position = position;                                      
}
    