#include "ShaderClass.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ShaderClass::ShaderClass(void)
{
	this->ID = 0;
	totalShaders = 0;
	shaders[0] = 0;
	shaders[1] = 0;
	shaders[2] = 0;
}

void ShaderClass::Use(void)
{
	glUseProgram(this->ID);
}

void ShaderClass::LoadShader(GLenum whichShader, const char* filename)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(filename);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		shaderCode = shaderStream.str();

	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}

	const char* charShaderCode = shaderCode.c_str();

	unsigned int shaderID = glCreateShader(whichShader);
	glShaderSource(shaderID, 1, &charShaderCode, NULL);
	glCompileShader(shaderID);
	//glEnable(GL_CULL_FACE); // nie renderuje tylnej sciany
	glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CCW);
	//sprawdzanie b³êdów
	int status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, infoLog);
		std::cerr << "Compile log: " << infoLog << std::endl;
		delete[] infoLog;
	}

	if (whichShader == GL_VERTEX_SHADER) {
		shaders[0] = shaderID; totalShaders++;
	}
	if (whichShader == GL_FRAGMENT_SHADER) {
		shaders[1] = shaderID; totalShaders++;
	}
	if (whichShader == GL_GEOMETRY_SHADER) {
		shaders[2] = shaderID; totalShaders++;
	}

}

void ShaderClass::Create_and_Link()
{
	ID = glCreateProgram();
	for (int i = 0; i < 3; i++)
	{
		if (shaders[i] != 0)
		{
			glAttachShader(ID, shaders[i]);
		}
	}

	//konsolidacja programu i sprawdzenie, czy przebieg³a prawid³owo
	int status;
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		int infoLogLength;

		glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(ID, infoLogLength, NULL, infoLog);
		std::cerr << "Link log: " << infoLog << std::endl;
		delete[] infoLog;
	}

	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
	glDeleteShader(shaders[2]);
}

void ShaderClass::SetBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ShaderClass::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderClass::SetFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderClass::Set2DVec(const std::string& name, glm::vec2 value)
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}

void ShaderClass::Set3DVec(const std::string& name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void ShaderClass::Set4DVec(const std::string& name, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void ShaderClass::Set2Mat(const std::string& name, glm::mat2 value)
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderClass::Set3Mat(const std::string& name, glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderClass::Set4Mat(const std::string& name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}