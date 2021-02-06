#include "AppWindow.h"
#include "EngineTime.h"
#include "Vector3D.h"
#include <Windows.h>
#include "Matrix4.h"
#include "InputSystem.h"
#include "UIManager.h"
#include "Prerequisites.h"
#include <iostream>
#include "GameObjectManager.h"
#include "ShaderLibrary.h"
#include "BaseSystem.h"

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}


void AppWindow::onCreate()
{

	Window::onCreate();
	
	InputSystem::getInstance()->addListener(this);
	InputSystem::getInstance()->showCursor(true);
	
	RECT rc = this->getClientWindowRect();
	ShaderLibrary::initialize();

	
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	

	GameObjectManager::initialize();

	SceneCameraHandler::initialize();
	UIManager::initialize(this->m_hwnd);
	BaseSystem::initializs();

}

void AppWindow::onUpdate()
{
	
	Window::onUpdate();

	InputSystem::getInstance()->update();

	
	if (speed <= 0) {
		increase = true;
	}

	if (speed < 10.0f && increase) {
		speed += EngineTime::getDeltaTime();
	}

	else if(speed > 10.0f || !(increase)){
		increase = false;
		speed -= EngineTime::getDeltaTime();
	}

	
	
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();

	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;


	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(width, height);
	

	//GameObjectManager::getInstance()->updateAll();
	GameObjectManager::getInstance()->renderAll(width, height);
	UIManager::getInstance()->drawAllUI();


	SceneCameraHandler::getInstance()->update();

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	m_swap_chain->present(true);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onDefocus()
{
	InputSystem::getInstance()->removeListener(this);
}


void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		rotX += 3.14f * m_delta_time;
	}
	else if (key == 'S')
	{
		rotX -= 3.14f * m_delta_time;
	}
	else if (key == 'A')
	{
		rotY += 3.14f * m_delta_time;
	}
	else if (key == 'D')
	{
		rotY -= 3.14f * m_delta_time;
	}
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
}
