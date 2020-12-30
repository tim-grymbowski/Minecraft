#version 350

in vec3 position;

uniform sampler2D texture;

void main()
{
	frag_Color = vec4(position, 1.0);
}