#include "CreditsScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

CreditsScreen::CreditsScreen()
{
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::drawUI()
{
	FLOAT clear_color[] = { 0, 0.3f, 0.4f, 1 };
	ImGui::Begin("Credits");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 245, 100));
	ImGui::SetWindowSize(ImVec2(210, UIManager::WINDOW_HEIGHT - 287));
	
	ImGui::Text("Developer: Marco Malabag\n");
	ImGui::Text("References: Parcode\n Sir Niel\n https://github.com/ocornut/imgui for the ImGui files");
	ImGui::End();
}


