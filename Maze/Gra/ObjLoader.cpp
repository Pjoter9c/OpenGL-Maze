#include "ObjLoader.h"

#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



void ObjLoader::LoadObj(const std::string filename, const char* textureName)
{
	vertices.clear();
	indices.clear();

	std::vector <glm::vec3> vList;
	std::vector <glm::vec3> nList;
	std::vector <glm::vec2> uvList;

	std::string objCode;
	std::ifstream objFile;

	objFile.open(filename);
	std::stringstream objStream;
	objStream << objFile.rdbuf();
	objFile.close();

	objCode = objStream.str();

	while (std::getline(objStream, objCode))
	{
		std::istringstream iss(objCode);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v")
		{
			glm::vec3 vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			vList.push_back(vertex);
		}

		if (prefix == "vn") {
			glm::vec3 normal;
			iss >> normal.x >> normal.y >> normal.z;
			nList.push_back(normal);
		}

		if (prefix == "vt") {
			glm::vec2 uv;
			iss >> uv.x >> uv.y;
			uvList.push_back(uv);
		}


		if (prefix == "f")
		{
			unsigned int value;
			std::string ind;
			std::string uv;
			std::string vn;
			while (!iss.eof())
			{
				std::getline(iss, ind, '/');
				value = std::stoi(ind);
				indices.push_back(value - 1);

				std::getline(iss, uv, '/');

				std::getline(iss, vn, ' ');

				Vertex vert;
				vert.Position = vList[std::stoi(ind) - 1];
				vert.Normal = nList[std::stoi(vn) - 1];
				vert.TexCoords = uvList[std::stoi(uv) - 1];
				
				listOfVertices.push_back(vert.Position.x);
				listOfVertices.push_back(vert.Position.y);
				listOfVertices.push_back(vert.Position.z);

				listOfVertices.push_back(vert.Normal.x);
				listOfVertices.push_back(vert.Normal.y);
				listOfVertices.push_back(vert.Normal.z);

				listOfVertices.push_back(vert.TexCoords.x);
				listOfVertices.push_back(vert.TexCoords.y);
				


				//vertices.push_back(vert);
			}
		}
	}
	CreateMesh(textureName);
}

void ObjLoader::CreateMesh(const char* textureName) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, listOfVertices.size() * sizeof(float), &listOfVertices[0], GL_STATIC_DRAW);
	//indeksy wierzcho³ków
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	//vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//vertex normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//vertex uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	
	//tekstura
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	//texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//load image, create texture, generate mipmaps
	stbi_set_flip_vertically_on_load(true);
	
	unsigned char* data = stbi_load(textureName, &tex_width, &tex_height, &tex_nr_channels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
	
}

void ObjLoader::Draw() {
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawArrays(GL_TRIANGLES, 0, indices.size());
	glBindVertexArray(0);
}

void ObjLoader::Delete() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}