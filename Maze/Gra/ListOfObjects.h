#pragma once

#include<vector>

#include "ObjLoader.h"

class ListOfObjects
{
	std::vector<ObjLoader> Objects;
public:
	void Add(ObjLoader Mesh);
	void Draw();
};

