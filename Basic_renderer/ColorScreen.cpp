#include "ColorScreen.h"

ColorScreen::ColorScreen()
{
}

ColorScreen::~ColorScreen()
{
}

void ColorScreen::drawUI()
{
	float clear_color[] = { 0.0f, 0.3f, 0.4f, 1.0f };
	
	ImGui::Begin("Color UI");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 345, 400));
	ImGui::SetWindowSize(ImVec2(210, UIManager::WINDOW_HEIGHT - 287));
	ImGui::ColorEdit4("MyColor", clear_color);
	ImGui::End();
}
