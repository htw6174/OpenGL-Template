#version 430

#define VERTEX_DRIFT .0

out vec3 tcsPos;

layout (location=0) in vec3 position;

void main(void)
{
	tcsPos = position;
	gl_Position =  vec4(position, 1.0);
}
