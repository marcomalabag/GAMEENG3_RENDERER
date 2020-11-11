#pragma once
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class DrawQuad
{
public:
	static DrawQuad* getInstance();
	static void initialize();
	static void destroy();
	void drawQuads();

private:
	DrawQuad();
	~DrawQuad();
	DrawQuad(DrawQuad const&) {};
	DrawQuad& operator=(DrawQuad const&) {};
	static DrawQuad* sharedInstance;


};

