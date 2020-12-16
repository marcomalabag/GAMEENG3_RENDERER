#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include "Cube.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <vector>
#include "InputListener.h";

typedef std::vector<Cube*> Cubes;

class EngineTime;
class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onFocus();
	virtual void onDefocus();

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* MyIndexBuffer;
	Cubes MyCubes;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	bool increase;
	float speed = 0.0f;
	float m_angle = 0;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
	float m_time;

	float rotX = 0.0f;
	float rotY = 0.0f;

private:
	friend class EngineTime;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos)override;
	virtual void onLeftMouseUp(const Point& mouse_pos)override;
	virtual void onRightMouseDown(const Point& mouse_pos)override;
	virtual void onRightMouseUp(const Point& mouse_pos)override;
};

