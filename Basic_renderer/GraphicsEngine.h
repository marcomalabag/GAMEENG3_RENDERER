#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"

class GraphicsEngine
{
private:
	GraphicsEngine();
	~GraphicsEngine();

public:
	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();
	MeshManager* getMeshManager();
	void getVertexMeshLayoutShaderByteCodeAndSize(void ** byte_code, size_t* size);
public:
	static GraphicsEngine* get();
	static void create();
	static void release();

private:
	RenderSystem* RSystem = nullptr;
	TextureManager* TextManager = nullptr;
	MeshManager* MshManager = nullptr;
	static GraphicsEngine* MyEngine;

	unsigned char MyMeshLayoutByteCode[1024];
	size_t MyMeshLayoutSize = 0;
};