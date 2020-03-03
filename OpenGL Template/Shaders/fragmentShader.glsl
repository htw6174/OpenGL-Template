#version 430
out vec4 color;
void main(void)
{
	color = vec4(gl_FragCoord.z / 600, gl_FragCoord.y / 600, gl_FragCoord.x / 600, 1.0);
}