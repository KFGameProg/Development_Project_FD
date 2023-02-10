#layout 440 core

out vec4 FragColour;

in vec2 uv;
uniform sampler2D u_texture;

void main(){
	FragColour = texture(u_texture, uv);
}
