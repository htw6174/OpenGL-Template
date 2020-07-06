#version 430

#define VERTEX_DRIFT .3

in vec3 tesPos[];

layout (triangles, equal_spacing, ccw) in; // TRY BOTH WAYS

uniform mat4 mv_matrix;
uniform mat4 m_matrix;
uniform mat4 proj_matrix;
uniform int objectId;

out vec3 geomWorldPosition;

float rand(float x)
{
    return fract(sin(x) * 100000.0);
}

// Will only work with one winding order
vec3 GetNormal(vec3 a, vec3 b, vec3 c)
{
   vec3 i = a - b;
   vec3 j = c - b;
   return normalize(cross(j, i));
}

void main()
{
	vec3 modelPosition = vec3(gl_TessCoord.x) * tesPos[0] + 
		 vec3(gl_TessCoord.y) * tesPos[1] + 
		 vec3(gl_TessCoord.z) * tesPos[2];

	float posHash = modelPosition.x + modelPosition.y + modelPosition.z;

	// make a sphere
	modelPosition = normalize(modelPosition);
	
	// displacing along normal
	modelPosition = modelPosition + modelPosition*VERTEX_DRIFT * (rand(posHash + objectId) * 2. - 1.);

	geomWorldPosition = (m_matrix * vec4(modelPosition, 1.0)).xyz;
	gl_Position = proj_matrix * mv_matrix * vec4(modelPosition, 1.0);
}
