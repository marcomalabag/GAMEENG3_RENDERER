#include "InspectorScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

InspectorScreen::InspectorScreen() :AUIScreen("ProfilerScreen")
{
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::updateTransformDisplays()
{
	Vector3D pos = this->SelectedObject->getLocalPosition();
	this->position[0] = pos.getX();
	this->position[1] = pos.getY();
	this->position[2] = pos.getZ();

	Vector3D rot = this->SelectedObject->getLocalRotation();
	this->rotation[0] = rot.getX();
	this->rotation[1] = rot.getY();
	this->rotation[2] = rot.getZ();

	Vector3D scale = this->SelectedObject->getLocalScale();
	this->scale[0] = scale.getX();
	this->scale[1] = scale.getY();
	this->scale[2] = scale.getZ();
}

void InspectorScreen::TransformUpdate()
{
	if (this->SelectedObject != NULL) {
		this->SelectedObject->setPosition(Vector3D(this->position[0], this->position[1], this->position[2]));
		this->SelectedObject->setRotation(Vector3D(this->rotation[0], this->rotation[1], this->rotation[2]));
		this->SelectedObject->setScale(Vector3D(this->scale[0], this->scale[1], this->scale[2]));
	}
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector Window");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 275, 20));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
	this->SelectedObject = GameObjectManager::getInstance()->getSelectedObject();
	if (this->SelectedObject != NULL) {
		String name = this->SelectedObject->getName();
		ImGui::Text("Selected Object is: %s", name.c_str());
		this->updateTransformDisplays();
		if (ImGui::InputFloat3("Position", this->position, 4)) { this->TransformUpdate(); }
		if (ImGui::InputFloat3("Rotation", this->rotation, 4)) { this->TransformUpdate(); }
		if (ImGui::InputFloat3("Scale", this->scale, 4)) { this->TransformUpdate(); }
		
	}
	ImGui::End();
}
