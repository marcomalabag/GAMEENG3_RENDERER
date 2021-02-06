#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>


GraphicsEngine* GraphicsEngine::MyEngine = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		this->RSystem = new RenderSystem();
	}
	catch (...) { throw std::exception("RenderSystem not created successfully"); }

	try
	{
		this->TextManager = new TextureManager();
	}
	catch (...) { throw std::exception("TextureManager not created successfully"); }

	try
	{
		
		this->MshManager = new MeshManager();
	}
	catch (...) { throw std::exception("MeshManager not created successfully"); }

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	this->RSystem->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(MyMeshLayoutByteCode, shader_byte_code, size_shader);
	MyMeshLayoutSize = size_shader;
	this->RSystem->releaseCompiledShader();
}




void GraphicsEngine::release()
{
	if (!GraphicsEngine::MyEngine) return;
	delete GraphicsEngine::MyEngine;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::MyEngine = nullptr;
	delete this->RSystem;
	delete this->TextManager;
	delete this->MshManager;
}


RenderSystem* GraphicsEngine::getRenderSystem()
{
	return this->RSystem;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return this->TextManager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return this->MshManager;
}

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = MyMeshLayoutByteCode;
	*size = MyMeshLayoutSize;
}

GraphicsEngine* GraphicsEngine::get()
{
	return MyEngine;
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::MyEngine) {
		throw std::exception("Graphics Engine already created");
	}

	GraphicsEngine::MyEngine = new GraphicsEngine();
}





