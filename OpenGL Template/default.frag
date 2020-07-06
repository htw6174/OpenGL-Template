#version 430

in vec4 varyingColor;
out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform vec3 tint;

void main(void)
{
	vec3 tinty = vec3(1.0f, 0.0f, 0.0f);
	color = vec4(tinty, 1.);
}