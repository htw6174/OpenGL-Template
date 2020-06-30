#version 430

in vec4 varyingColor;
out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform vec3 tint;

void main(void)
{
	color = vec4(tint, 1.);
}