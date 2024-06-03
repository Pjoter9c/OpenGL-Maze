#pragma once
class Collision
{
public:
	float minX, minZ, maxX, maxZ;
	Collision(float newX, float newZ);
	float getMinX();
	float getMaxX();
	float getMinZ();
	float getMaxZ();

};

