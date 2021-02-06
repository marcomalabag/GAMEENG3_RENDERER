#include "ProfileScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

ProfileScreen::ProfileScreen():AUIScreen("ProfilerScreen")
{
}

ProfileScreen::~ProfileScreen()
{
}

void ProfileScreen::drawUI()
{
	ImGui::Begin("Engine Profiler");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 100.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}
