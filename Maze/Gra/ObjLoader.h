#pragma once

#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderClass.h"


class Vertex
{
public:
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class ObjLoader
{
public:
	std::vector<unsigned int> indices; //lista indeksów
	void LoadObj(const std::string filename, const char* textureName); //wczytywanie pliku obj i zapisywanie danych do list
	std::vector<Vertex> vertices;
	std::vector<float> listOfVertices;

	unsigned int VAO, VBO, EBO, textureID;
	int tex_width, tex_height, tex_nr_channels;
	void CreateMesh(const char* textureName);
	void Draw();
	void Delete();
};