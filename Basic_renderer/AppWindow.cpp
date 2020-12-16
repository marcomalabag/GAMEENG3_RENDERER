#include "AppWindow.h"
#include "EngineTime.h"
#include "Vector3D.h"
#include <Windows.h>
#include "Matrix4.h"
#include "InputSystem.h"
#include "UIManager.h"


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

	InputSystem::initialize();

	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	UIManager::initialize(this->m_hwnd);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	for (int i = 0; i < 100; i++) {
		float x = (rand() % (-100 - 100)) / 100.0;
		float y = (rand() % (-100 - 100)) / 100.0;
		float Rspeed = (rand() % (-135 - 135)) / 100.0;

		Cube* cube = new Cube("Cube", shader_byte_code, size_shader);
		cube->setAnimSpeed(3.45f);
		cube->setPosition(Vector3D(x, y, 0.0f));
		
		cube->setScale(Vector3D(0.25f, 0.25f, 0.25f));
		this->MyCubes.push_back(cube);
	}

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	SceneCameraHandler::initialize();
}

void AppWindow::onUpdate()
{
	
	Window::onUpdate();
	UIManager::getInstance()->drawAllUI();

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

	std::cout << "Frames have passed:" << speed << "\n";

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();

	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	for (int i = 0; i < MyCubes.size(); i++) {
		this->MyCubes[i]->update(EngineTime::getDeltaTime());
		this->MyCubes[i]->draw(width, height, m_vs, m_ps, rotX, rotY);
	}


	SceneCameraHandler::getInstance()->update();

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	m_swap_chain->present(true);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
	SceneCameraHandler::destroy();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onDefocus()
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
