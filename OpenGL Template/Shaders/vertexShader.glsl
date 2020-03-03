#version 430

layout (location=0) in vec3 position;

uniform float offset;
uniform mat4 ortho;

void main(void)
{
	gl_Position = vec4(position.x + offset, position.y - offset, 0.0f, 1.0f) * ortho;
}