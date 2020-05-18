#version 430

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture;

void main() {
	FragColor = texture(Texture, TexCoord);
}