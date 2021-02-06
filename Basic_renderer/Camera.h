#pragma once

#include "AGameObject.h"
#include "InputListener.h"
#include "Matrix4.h"
#include "InputSystem.h"
#include "Prerequisites.h"
#include <iostream>

class Camera: public AGameObject, public InputListener
{
public:
	Camera(String name);
	
    ~Camera();

	void update(float deltaTime) override;
	virtual void draw(int with, int height) override;
	Matrix4 getViewMatrix();

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;

	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

private:
	void updateViewMatrix();
	bool moveMouse = true;
	


};

