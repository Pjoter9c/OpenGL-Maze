#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderClass
{
public:
	ShaderClass();
	void LoadShader(GLenum whichShader, const char* filename); //wczytanie z pliku
	void Create_and_Link();//tworzenie i linkowanie shaderów do programu shadera
	void Use();
	void SetBool(const std::string& name, bool value);
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void Set2DVec(const std::string& name, glm::vec2 value);
	void Set3DVec(const std::string& name, glm::vec3 value);
	void Set4DVec(const std::string& name, glm::vec4 value);
	void Set2Mat(const std::string& name, glm::mat2 value);
	void Set3Mat(const std::string& name, glm::mat3 value);
	void Set4Mat(const std::string& name, glm::mat4 value);

private:
	unsigned int ID; //identyfikator programu shaderów
	unsigned int totalShaders; //liczba shaderów
	unsigned int shaders[3]; //wartoœæ int utworzonego ka¿dego shadera
};
