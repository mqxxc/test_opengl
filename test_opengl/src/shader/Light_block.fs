#version 330 core
out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 lightColo;

void main()
{
	FragColor = vec4(objColor * lightColo, 1.0);
}
