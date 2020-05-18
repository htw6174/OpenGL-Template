#version 430

layout (location=0) in vec3 position;
layout (location=2) in vec2 texCoord;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec2 texCoordV;

void main() {
	texCoordV = texCoord;
	gl_Position = proj * mv * position;
}
