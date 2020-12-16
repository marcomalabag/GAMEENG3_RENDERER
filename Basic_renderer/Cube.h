#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "Point.h"
#include "SceneCameraHandler.h"
#include <iostream>

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class Cube: public AGameObject, public InputListener
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader, float rotX, float rotY);
	void setAnimSpeed(float speed);

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
	float deltaScale = 0.0f;
	float deltaRotation = 0.0f;

	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;
};

