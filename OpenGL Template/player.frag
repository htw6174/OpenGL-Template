#version 430

#define LIGHTPOS vec3(0., 0., -1.)

in vec4 varyingColor;
in vec3 position;
in vec3 normal;
out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform vec3 tint;

void main(void)
{
	vec3 lightDir = normalize(LIGHTPOS - position);
	float diffuse = max(dot(lightDir, normal), 0.);
	color = vec4(diffuse * tint, 1.);
}