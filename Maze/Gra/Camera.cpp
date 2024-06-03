#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float speed, float angle) {

	Position = pos;
	Up = up;
	Front = front;
	Look = pos + front;
	Speed = speed;
	Angle = angle;
	Cross = glm::normalize(glm::cross(front, up));
}

glm::vec3 Camera::Move(float side, float upDown, float forward) {

	glm::vec3 pos = Position;
	pos += Cross * side * Speed;
	pos += Up * upDown * Speed;
	pos += Front * -forward * Speed;

	//Look = Position + Front;

	return pos;
}

void Camera::setPosition(glm::vec3 Pos) {
	Position = Pos;
	Look = Position + Front;
}

void Camera::Rotate(glm::vec3 axis) {
	glm::mat4 Model = glm::rotate(glm::mat4(1.0), Angle, axis);

	Up = glm::vec3(Model * glm::vec4(Up, 1.0));
	Front = glm::vec3(Model * glm::vec4(Front, 1.0));
	Cross = glm::vec3(Model * glm::vec4(Cross, 1.0));
	Look = Position + Front;
}

glm::vec3 Camera::getPosition() {
	return Position;
}

glm::vec3 Camera::getLook() {
	return Look;
}

glm::vec3 Camera::getFront() {
	return Front;
}

glm::vec3 Camera::getUp() {
	return Up;
}

glm::vec3 Camera::getCross() {
	return Cross;
}

float Camera::getSpeed() {
	return Speed;
}

void Camera::UpView() {

}

void Camera::NormalView() {

}