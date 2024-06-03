#include "ListOfObjects.h"

void ListOfObjects::Add(ObjLoader Mesh) {
	Objects.push_back(Mesh);
}

void ListOfObjects::Draw() {
	for (int i = 0; i < Objects.size(); i++)
		Objects[i].Draw();
}