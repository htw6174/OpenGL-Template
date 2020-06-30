#version 430

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 position;
out vec3 normal;

// Will only work with one winding order
vec3 GetNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(b, a));
}

void main(void)
{
	position = gl_in[0].gl_Position.xyz;
	normal = GetNormal();
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();
}