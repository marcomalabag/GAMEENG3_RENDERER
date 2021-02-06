#include "UIManager.h"
#include <iostream>

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::getInstance()
{
	return UIManager::sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	for (int i = 0; i < this->uiList.size(); i++) {
		if (i < this->uiList.size() - 2) {
			this->uiList[i]->drawUI();
		}
		if (this->RenderCredits && i == this->uiList.size() - 2) {
			this->uiList[i]->drawUI();
		}
		if (this->RenderColorUI && i == this->uiList.size() - 1) {
			this->uiList[i]->drawUI();
		}


	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::SetRenderCredits()
{
	this->RenderCredits = true;
}

void UIManager::SetColorUI()
{
	this->RenderColorUI = true;
}

UIManager::UIManager(HWND windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getRenderSystem()->m_d3d_device, GraphicsEngine::get()->getRenderSystem()->m_imm_context);

	UINames uiNames;
	ProfileScreen* profilescreen = new ProfileScreen();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilescreen;
	this->uiList.push_back(profilescreen);

	MenuScreen* menuscreen = new MenuScreen();
	this->uiTable[uiNames.MENU_SCREEN] = menuscreen;
	this->uiList.push_back(menuscreen);

	InspectorScreen* inspectorscreen = new InspectorScreen();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorscreen;
	this->uiList.push_back(inspectorscreen);

	Hierarchy* hierarchyscreen = new Hierarchy();
	this->uiTable[uiNames.HIERARCHY_SCREEN] = hierarchyscreen;
	this->uiList.push_back(hierarchyscreen);

	CreditsScreen* creditsscreen = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsscreen;
	this->uiList.push_back(creditsscreen);

	ColorScreen* colorscreen = new ColorScreen();
	this->uiTable[uiNames.COLOR_SCREEN] = colorscreen;
	this->uiList.push_back(colorscreen);
}

UIManager::~UIManager()
{
}
