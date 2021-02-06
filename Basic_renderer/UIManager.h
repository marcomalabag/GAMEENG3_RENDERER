#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "AUIScreen.h"
#include "window.h"
#include "UINames.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "GraphicsEngine.h"
#include "ProfileScreen.h"
#include "MenuScreen.h"
#include "Hierarchy.h"
#include "InspectorScreen.h"
#include "CreditsScreen.h"
#include "ColorScreen.h"

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();
	void SetRenderCredits();
	void SetColorUI();

	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 550;


private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;

	bool RenderCredits = false;
	bool RenderColorUI = false;
};

