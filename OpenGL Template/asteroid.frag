#version 430

in vec4 varyingColor;
out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform vec3 tint;

void main(void)
{
	vec3 col = varyingColor.xyz * tint;
	color = vec4(col, 1.);
}