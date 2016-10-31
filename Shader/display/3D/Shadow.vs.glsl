#version 420 core

//outgoing tesselation coordinates
in vec4 position;   
out vec2 texCoord;
 
uniform ivec2 dimensions;


void main(void)
{  
        texCoord = position.xz/vec2(dimensions);
        gl_Position = position;                                      
}
    