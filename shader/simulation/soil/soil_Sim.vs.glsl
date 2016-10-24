/*
 * Sample dummy shader to check the highlighter plugin.
 */

#version 430 core

void main() 
{
    const vec4 vertices[] = vec4[](vec4(-1.0, -1.0, 0.5, 1.0),
                                   vec4( 1.0, -1.0, 0.5, 1.0),
                                   vec4(-1.0, 1.0,  0.5, 1.0),
                                   vec4( 1.0, 1.0, 0.5, 1.0));
     //move vertex
    gl_Position = vertices[gl_VertexID];
}
