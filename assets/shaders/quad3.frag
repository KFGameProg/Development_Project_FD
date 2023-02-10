#version 440 core
			
layout(location = 0) out vec4 colour;

in vec2 texCoord;
in flat int texUnit;
in vec4 tint;

uniform sampler2D[32] u_texData;

void main()
{
	colour = texture(u_texData[texUnit], texCoord) * tint;
}