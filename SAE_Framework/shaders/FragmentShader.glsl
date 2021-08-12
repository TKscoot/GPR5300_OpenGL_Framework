#version 450 core

in vec3 normal;
in vec3 vertPosition;

uniform vec3 cameraPos;

out vec4 FragColor;

void main()
{
	vec3 lightDir = vec3(-0.5, 1.0, 0.0);

	// diffuse
	vec3 diffuseColor = clamp(dot(lightDir, normal), 0.0, 1.0) * vec3(1.0, 0.0, 0.0);

	// specular
	vec3 viewDir = normalize(cameraPos - vertPosition);
	vec3 reflectDir = reflect(-lightDir, normal);

	float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);

	vec3 specularColor = vec3(0.5) * specFactor;



	FragColor = vec4(diffuseColor + specularColor, 1.0);
}