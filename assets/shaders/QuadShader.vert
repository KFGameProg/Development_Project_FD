/*#version 440 core

layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec2 a_uv;
uniform mat4 u_model;
uniform mat4 u_screen;

out vec2 uv;

void main(){
	uv = a_uv;
	gl_Position = u_screen * u_model * vec4(a_pos, 1.0);
}*/