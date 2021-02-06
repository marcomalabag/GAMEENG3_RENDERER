#include "ShaderLibrary.h"
#include <iostream>

ShaderLibrary* ShaderLibrary::sharedInstance = NULL;

ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(vertexShaderName.c_str(), "vsmain", shaderByteCode, sizeShader);
}

VertexShaderPtr ShaderLibrary::getVertexShader(String vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL) {
		std::cout << "No vertex shader available" << "\n";
	}

	return this->activeVertexShaders[vertexShaderName];
}

PixelShaderPtr ShaderLibrary::getPixelShader(String pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL) {
		std::cout << "No pixel shader available" << "\n";
	}
	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{
	ShaderData shaderdata;
	ShaderNames names;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(names.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderdata.shaderByteCode, &shaderdata.SizeShader);
	this->activeVertexShaders[names.TEXTURED_VERTEX_SHADER_NAME] = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shaderdata.shaderByteCode, shaderdata.SizeShader);

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(names.TEXTURED_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderdata.shaderByteCode, &shaderdata.SizeShader);
	this->activePixelShaders[names.TEXTURED_PIXEL_SHADER_NAME] = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderdata.shaderByteCode, shaderdata.SizeShader);
	
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(names.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderdata.shaderByteCode, &shaderdata.SizeShader);
	this->activeVertexShaders[names.BASE_VERTEX_SHADER_NAME] = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shaderdata.shaderByteCode, shaderdata.SizeShader);

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(names.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderdata.shaderByteCode, &shaderdata.SizeShader);
	this->activePixelShaders[names.BASE_PIXEL_SHADER_NAME] = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderdata.shaderByteCode, shaderdata.SizeShader);
}

ShaderLibrary::~ShaderLibrary()
{
}
