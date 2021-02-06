#include "PhysicsCube.h"
#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(String name): Cube(name, this->shader_byte_code, this->size_shader)
{
	this->setPosition(0.0f, 5.0f, 0.0f);
	this->setScale(1.0f, 1.0f, 1.0f);
	this->updateLocalMatrix();
	this->attachComponent(new PhysicsComponent("PhysicsComponent", this));
}

PhysicsCube::~PhysicsCube()
{
}

void PhysicsCube::update(float deltaTime)
{
	Cube::update(deltaTime);
}

void PhysicsCube::draw(int width, int height)
{
	Cube::draw(width, height);
}
