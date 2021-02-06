#pragma once
#include "Cube.h"

class PhysicsCube: public Cube
{
public:
	PhysicsCube(String name);
	~PhysicsCube();
	void* shader_byte_code = NULL;
	size_t size_shader = 0;

	void update(float deltaTime) override;
	void draw(int width, int height) override;

protected:
	float mass = 3.0f;
};

