#version 330 core
in vec3 ourColor;

out vec4 color;

uniform vec3 baseColor;

void main()
{
	color = vec4(baseColor * ourColor, 1.0f);
}