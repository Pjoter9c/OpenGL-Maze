#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "Collision.h"
class ListOfCollisions
{
	float minX, maxX, minZ, maxZ;
public:
	std::vector<Collision> Walls;
	void Create(const std::string fileName);
	bool detectCollision(glm::vec3 Pos);
	float getminX();
	float getmaxX();
	float getminZ();
	float getmaxZ();
};

