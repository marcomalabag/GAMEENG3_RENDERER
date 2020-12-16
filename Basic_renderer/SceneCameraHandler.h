#pragma once
#include "Camera.h"
#include "Matrix4.h"
#include "EngineTime.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void update();

	Matrix4 getSceneCameraViewMatrix();

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};
	static SceneCameraHandler* sharedInstance;

	Camera* sceneCamera;

};

