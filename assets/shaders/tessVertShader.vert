#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec3 posWS;
out vec2 uv;
out vec3 camera;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 camPos;

void main()
{
	posWS = vec3(model * vec4(aPos, 1.0)).xyz;
	uv = vec2(aUV.x, aUV.y);
	camera = camPos;

	gl_Position = model * vec4(aPos,1.0);
}