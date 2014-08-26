#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D texSampler;

void main(){
	color = vec4(texture( texSampler, UV ).rgb,0);
}