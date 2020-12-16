#include "Camera.h"

Camera::Camera(string name):AGameObject(name)
{
	this->setPosition(0.0f, 0.0f, -4.0f);
	this->updateViewMatrix();
	InputSystem::getInstance()->addListener(this);
}


Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.getX();
	float y = localPos.getY();
	float z = localPos.getZ();
	float moveSpeed = 10.0f;

	if (InputSystem::getInstance()->isKeyDown('W')) {
		z += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
		
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		z -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::draw(int with, int height, VertexShader* vertexShader, PixelShader* pixelShader, float rotX, float rotY)
{
}

Matrix4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point& delta_mouse_pos)
{
	if (this->moveMouse) {
		Vector3D localRotation = this->getLocalRotation();
		float x = localRotation.getX();
		float y = localRotation.getY();
		float z = localRotation.getZ();

		float speed = 0.05f;
		x += delta_mouse_pos.x * speed;
		
		y += delta_mouse_pos.y * speed;
		

		this->setRotation(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
	this->moveMouse = true;
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
	this->moveMouse = false;
}

void Camera::updateViewMatrix()
{
	Matrix4 worldCam;
	worldCam.setIdentity();

	Matrix4 temp;
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.getX());
	worldCam = worldCam.MultiplyMatrix(temp);

	temp.setRotationY(localRot.getY());
	worldCam = worldCam.MultiplyMatrix(temp);

	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.MultiplyMatrix(temp);

	worldCam.inverse();
	this->localMatrix = worldCam;
}
