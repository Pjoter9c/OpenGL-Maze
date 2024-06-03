#version 430 core


in vec3 ObjPos;
in vec3 aNormal;
in vec2 UV;

uniform vec3 CamPos;
uniform vec4 TriangleColor;
uniform sampler2D TextureSampler;
uniform float ambientValue;

out vec4 FragColor;



void main()
{
	vec3 LightColor = vec3(1.0, 1.0, 1.0) * 0.5f;
	vec3 LightPos = CamPos;

	vec3 ambient = ambientValue * LightColor;

	float diffuseValue = 1.0;
	vec3 LightDir = normalize(LightPos - ObjPos);
	float diffuseStrength = max(dot(LightDir, aNormal), 0.0);
	vec3 diffuse = diffuseValue * diffuseStrength * LightColor;

	float specularValue = 0.5;
	vec3 ViewDir = normalize(LightPos - ObjPos);
	vec3 ReflectDir = reflect(LightDir, aNormal);
	float specularStrength = pow(max(dot(ViewDir, ReflectDir), 0.0), 32);
	vec3 specular = specularValue * specularStrength * LightColor;

	vec3 LightResult = ambient + diffuse + specular;
	vec3 FinalColor = LightResult * vec3(TriangleColor);
	
	float Fade = length(ObjPos - CamPos);
	FinalColor = 1/Fade * FinalColor;
	FragColor = texture(TextureSampler, UV) * vec4(FinalColor, 1.0);
}