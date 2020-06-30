#version 430

#define VERTEX_DRIFT .8

in int gl_VertexID;
in int gl_DrawID;

layout (location=0) in vec3 position;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform int objectId;

out vec4 varyingColor;

float rand(float x)
{
    return fract(sin(x) * 100000.0);
}

void main(void)
{
	float posHash = position.x + position.y + position.z;
	vec3 pos = position + VERTEX_DRIFT * (rand(posHash + objectId) * 2. - 1.);
	gl_Position = proj_matrix * mv_matrix * vec4(pos,1.0);
	varyingColor = vec4(vec3(rand(floor(gl_VertexID / 3))), 1.) + 0.1;
	//varyingColor = vec4(position,1.0)*0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}
