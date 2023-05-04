#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aTan;
layout (location = 4) in vec3 aBiTan;

out vec3 posWS;
out vec3 normWS;
out vec2 uv;
out mat3 TBN;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0);

	posWS = vec3(model * vec4(aPos, 1.0)).xyz;
	normWS = mat3(transpose(inverse(model))) * aNormal;
	uv = vec2(aUV.x, aUV.y);
	vec3 T = (model * vec4(aTan, 0.0)).xyz;
    vec3 B = (model * vec4(aBiTan, 0.0)).xyz;
	TBN = mat3(T, B, normWS);
}