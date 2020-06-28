#version 430

layout (location=0) in vec3 position;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varyingColor;

void main(void)
{
	vec3 pos = position * 2.;
	gl_Position = proj_matrix * mv_matrix * vec4(pos,1.0);
} 
