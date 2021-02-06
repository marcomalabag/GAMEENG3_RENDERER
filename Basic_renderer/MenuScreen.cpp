#include "MenuScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <iostream>
#include "GameObjectManager.h"
#include "Prerequisites.h"

MenuScreen::MenuScreen()
{

}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W")) {/*Do something */ }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Cube")) { this->CreateCube(); }
			if (ImGui::MenuItem("Create Textured Cube")) { this->CreateTexturedCube(); }
			if (ImGui::MenuItem("Create Sphere")) { /* Do stuff */ }
			if (ImGui::MenuItem("Create Plane")) { this->CreatePlane(); }
			if (ImGui::MenuItem("Create Bunny")) { this->CreateBunny(); }
			if (ImGui::MenuItem("Create Statue")) { this->CreateStatue(); }
			if (ImGui::MenuItem("Create Teapot")) { this->CreateTeapot(); }
			if (ImGui::MenuItem("Create Physics_Cube")) { this->CreatePhysicsCube(); }
			if (ImGui::BeginMenu("Light")) {
				if (ImGui::MenuItem("Point Light")) { /* Do stuff */ }
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Color Picker")) { this->OpenColorUI(); }
		if (ImGui::BeginMenu("About")) {
			if (ImGui::MenuItem("Credits")) { this->OpenCreditsUI(); }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

}

void MenuScreen::CreateCube()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	ShaderNames names;

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::CUBE, shader_byte_code, size_shader);
}

void MenuScreen::CreateTexturedCube()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	ShaderNames names;

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::TEXTUREDCUBE, shader_byte_code, size_shader);
}

void MenuScreen::CreateTeapot()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	ShaderNames names;

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::TEAPOT, shader_byte_code, size_shader);
}

void MenuScreen::CreateStatue()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	ShaderNames names;

	

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::STATUE, shader_byte_code, size_shader);
}

void MenuScreen::CreateBunny()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	ShaderNames names;

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::BUNNY, shader_byte_code, size_shader);

}

void MenuScreen::CreatePlane()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	ShaderNames names;

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PLANE, shader_byte_code, size_shader);
}

void MenuScreen::OpenColorUI()
{	
	UIManager::getInstance()->SetColorUI();
}

void MenuScreen::CreatePhysicsCube()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	ShaderNames names;

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PHYSICS_CUBE, shader_byte_code, size_shader);
}

void MenuScreen::OpenCreditsUI()
{
	UIManager::getInstance()->SetRenderCredits();
}
