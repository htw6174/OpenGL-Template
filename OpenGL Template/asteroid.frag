#version 430

#define LIGHT_AMBIENT vec3(.08);
#define LIGHT_DIFFUSE vec3(.2, 1., .2)
#define FALLOFF 2000.

in vec3 fragWorldPosition;
in vec3 normal;
out vec4 color;

uniform vec3 tint;
uniform vec3 lightPos;

vec3 lighting(vec3 surface, vec3 normal, vec3 light)
{
	vec3 ambient = LIGHT_AMBIENT;

	vec3 xyDifference = light - fragWorldPosition;
	vec3 lightDir = normalize(xyDifference);
	float dotLN = max(dot(lightDir, normal), 0.);
	float distanceToLight = length(xyDifference);
	distanceToLight *= distanceToLight * distanceToLight;
	float diffuseIntensity = max(1. - (distanceToLight / FALLOFF), 0.);
	vec3 diffuse = dotLN * LIGHT_DIFFUSE * diffuseIntensity;

	return ambient + diffuse;
}

void main(void)
{
	vec3 lightCol = lighting(fragWorldPosition, normal, lightPos);
	color = vec4(tint * lightCol, 1.);
	//color = vec4(diffuseIntensity, 1.0f);
	//if (worldPosition.y > 1.){color = vec4(1., 0., 0., 1.);}
}