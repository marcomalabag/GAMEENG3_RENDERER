#pragma once
#include <iostream>
#include <unordered_map>
#include "Prerequisites.h"
#include "ShaderNames.h"
#include "GraphicsEngine.h"

class ShaderLibrary
{
public:
	class ShaderData {
	public:
		void* shaderByteCode = nullptr;
		size_t SizeShader = 0;
	};

	typedef std::wstring String;
	typedef std::unordered_map<String, VertexShaderPtr> VertexShaderTable;
	typedef std::unordered_map<String, PixelShaderPtr> PixelShaderTable;

	static ShaderLibrary* getInstance();
	static void initialize();
	static void destroy();

	void requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader);
	VertexShaderPtr getVertexShader(String vertexShaderName);
	PixelShaderPtr getPixelShader(String pixelShaderName);


private:
	ShaderLibrary();
	~ShaderLibrary();
	ShaderLibrary(ShaderLibrary const&) {};
	ShaderLibrary& operator=(ShaderLibrary const&){};
	static ShaderLibrary* sharedInstance;

	VertexShaderTable activeVertexShaders;
	PixelShaderTable activePixelShaders;
};

