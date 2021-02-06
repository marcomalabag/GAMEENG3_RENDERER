#pragma once
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <d3d11.h>

class Mesh: public Resource
{
public:
	Mesh(const wchar_t* fullPath);
	~Mesh();
	const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();

private:
	VertexBufferPtr MyVertexBuffer;
	IndexBufferPtr MyIndexBuffer;

private:
	friend class DeviceContext;
};

