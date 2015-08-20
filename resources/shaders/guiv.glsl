#version 330 core

layout(location=0) in vec3 position;

attribute mat4 gui_MVP:

varying vec2 UV;

void main()
{
	gl_Position = vec4(vertexPosition,0,1);
	UV = vertexUV;
}