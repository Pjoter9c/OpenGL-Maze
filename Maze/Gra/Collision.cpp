#include "Collision.h"

Collision::Collision(float newX, float newZ) {
	minX = newX;
	minZ = newZ;
	maxX = newX;
	maxZ = newZ;
}

float Collision::getMinX() {
	return minX;
}

float Collision::getMaxX() {
	return maxX;
}

float Collision::getMinZ() {
	return minZ;
}

float Collision::getMaxZ() {
	return maxZ;
}
