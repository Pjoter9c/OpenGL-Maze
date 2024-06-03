#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
class Camera
{
private:
	glm::vec3 Position;
	glm::vec3 Look;
	glm::vec3 Up;
	glm::vec3 Cross;
	glm::vec3 Front;
	float Speed;
	float Angle;

public:

	Camera(glm::vec3 position, glm::vec3 front, glm::vec3 Up, float speed, float angle);

	glm::vec3 getPosition();

	glm::vec3 getLook();

	glm::vec3 getUp();

	glm::vec3 getFront();

	glm::vec3 getCross();

	void setPosition(glm::vec3 Pos);

	float getAngle();

	float getSpeed();

	glm::vec3 Move(float x, float y, float z);

	void Rotate(glm::vec3 axis);

	void UpView();

	void NormalView();
};

