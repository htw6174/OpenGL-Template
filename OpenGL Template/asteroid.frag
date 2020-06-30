#version 430

#define LIGHT_AMBIENT vec3(.5);
#define LIGHT_DIFFUSE vec3(.2, 1., .2)
#define FALLOFF 15.
#define DIFFUSE_BLEEDOVER .5

in vec4 varyingColor;
in vec3 position;
in vec3 normal;
out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform vec3 tint;
uniform vec3 lightPos;

vec3 lighting(vec3 surface, vec3 normal, vec3 light)
{
	vec3 ambient = LIGHT_AMBIENT;

	vec3 xyDifference = vec3(light.xy, 0.) - vec3(surface.xy, 0.);
	vec3 lightDir = normalize(xyDifference);
	float dotLN = max(dot(lightDir, normal) + DIFFUSE_BLEEDOVER, 0.);
	float distance = length(xyDifference);
	float diffuseIntensity = 1. - (distance / FALLOFF);
	vec3 diffuse = dotLN * LIGHT_DIFFUSE * diffuseIntensity;

	return ambient + diffuse;
}

void main(void)
{
	//vec3 col = varyingColor.xyz * tint;
	vec3 lightCol = lighting(position, normal, lightPos);
	color = vec4(tint * lightCol, 1.);
	//if (position.y > 1.){color = vec4(1., 0., 0., 1.);}
}