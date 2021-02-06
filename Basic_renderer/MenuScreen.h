#pragma once
#include "AUIScreen.h"
#include "UIManager.h"
#include "ShaderLibrary.h"
#include "ShaderNames.h"

class MenuScreen: public AUIScreen
{
public:
	MenuScreen();
	~MenuScreen();

	void drawUI();
	void CreateCube();
	void CreateTexturedCube();
	void CreateTeapot();
	void CreateStatue();
	void CreateBunny();
	void CreatePlane();
	void OpenCreditsUI();
	void OpenColorUI();
	void CreatePhysicsCube();
};

