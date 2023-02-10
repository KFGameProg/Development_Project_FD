#version 440 core
			
layout(location = 0) in vec2 a_vertexPosition;
layout(location = 1) in vec2 a_texCoord;

out vec2 texCoord;

uniform mat4 u_model;

layout(std140) uniform b_camera
{
	// Order is very important, must match UBO layout
	mat4 u_projection; 
	mat4 u_view;
};

void main()
{
	texCoord = a_texCoord;
	gl_Position =  u_projection * u_view * u_model * vec4(a_vertexPosition,1.0,1.0);
}

