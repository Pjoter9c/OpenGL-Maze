#include "ListOfCollisions.h"
#include <string>
#include <fstream>
#include <sstream>
#include<iostream>

float ListOfCollisions::getminX() { return minX; }
float ListOfCollisions::getmaxX() { return maxX; }
float ListOfCollisions::getminZ() { return minZ; }
float ListOfCollisions::getmaxZ() { return maxZ; }

bool ListOfCollisions::detectCollision(glm::vec3 Pos) {
	float threshold = 0.03f;
	bool collisionX;
	bool collisionZ;

	for (int i = 0; i < this->Walls.size(); i++) {
		collisionX = Pos.x + threshold >= this->Walls[i].getMinX() &&
			this->Walls[i].getMaxX() >= Pos.x - threshold;

		collisionZ = Pos.z + threshold >= this->Walls[i].getMinZ() &&
			this->Walls[i].getMaxZ() >= Pos.z - threshold;

		if (collisionX && collisionZ) {
			return true;
		}
	}
	return false;
}

void ListOfCollisions::Create(const std::string fileName) {
	Walls.clear();

	std::string objCode;
	std::ifstream objFile;

	objFile.open(fileName);
	std::stringstream objStream;
	objStream << objFile.rdbuf();
	objFile.close();

	objCode = objStream.str();

	bool New = true;
	float newX, newY, newZ;

	Collision obj(0.0, 0.0);

	while (std::getline(objStream, objCode))
	{
		std::istringstream iss(objCode);
		std::string prefix;
		iss >> prefix;

		if (prefix == "o")
		{
			New = true;
		}

		if (prefix == "v")
		{
			iss >> newX >> newY >> newZ;
			if (New) {
				obj.maxX = newX;
				obj.minX = newX;
				obj.maxZ = newZ;
				obj.minZ = newZ;
				New = false;
			}
			else {
				obj.maxX = glm::max(obj.maxX, newX);
				obj.maxZ = glm::max(obj.maxZ, newZ);
				obj.minX = glm::min(obj.minX, newX);
				obj.minZ = glm::min(obj.minZ, newZ);
			}
		}

		if (prefix == "s")
			Walls.push_back(obj);
	}

	minX = Walls[0].getMinX();
	minZ = Walls[0].getMinZ();
	maxX = Walls[0].getMaxX();
	maxZ = Walls[0].getMaxZ();

	for (int i = 1; i < Walls.size(); i++) {
		minX = glm::min(minX, Walls[i].getMinX());
		minZ = glm::min(minZ, Walls[i].getMinZ());
		maxX = glm::max(maxX, Walls[i].getMaxX());
		maxZ = glm::max(maxZ, Walls[i].getMaxZ());
	}

}