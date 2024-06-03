#version 430 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UvPos;

uniform mat4 u_ProjMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

out vec3 ObjPos;
out vec3 aNormal;
out vec2 UV;


void main()
{
	gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * vec4(Pos, 1.0);
	ObjPos = vec3(u_ModelMatrix * vec4(Pos, 1.0));
	aNormal = mat3(transpose(inverse(u_ModelMatrix))) * Normal;
	UV = UvPos;
}