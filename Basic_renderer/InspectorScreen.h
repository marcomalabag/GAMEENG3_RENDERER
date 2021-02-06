#pragma once
#include "AUIScreen.h"
#include "AGameObject.h"
#include "UIManager.h"
#include "GameObjectManager.h"

class InspectorScreen : public AUIScreen
{
public:
	InspectorScreen();
	~InspectorScreen();
	void updateTransformDisplays();
	void TransformUpdate();
	void drawUI();

private:
	AGameObject* SelectedObject = NULL;
	float position[3] = { 0.0f, 0.0f, 0.0f };
	float rotation[3] = { 0.0f, 0.0f, 0.0f };
	float scale[3] = { 1.0f, 1.0f, 1.0f };


public:
	friend class UIManager;
};

