#version 440 core
			
layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec3 a_vertexNormal;
layout(location = 2) in vec2 a_texCoord;
layout(location = 3) in mat4 a_model;
layout(location = 7) in int a_texUnit; // MATERIAL m_texture
layout(location = 8) in vec4 a_tint; // MATERIAL m_tint

out vec3 fragmentPos;
out vec3 normal;
out vec2 texCoord;
out flat int texUnit;
out vec4 tint;

layout (std140) uniform b_camera
{
	mat4 u_view;
	mat4 u_projection;
};

void main()
{
	mat4 MVP = u_projection * u_view * a_model;
	fragmentPos = vec3(a_model * vec4(a_vertexPosition, 1.0));
	normal = mat3(transpose(inverse(a_model))) * a_vertexNormal;
	texCoord = vec2(a_texCoord.x, a_texCoord.y);
	texUnit = a_texUnit;
	tint = a_tint;
	gl_Position =  MVP * vec4(a_vertexPosition,1.0);
}