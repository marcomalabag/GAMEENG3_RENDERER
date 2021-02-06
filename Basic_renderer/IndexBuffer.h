#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(void* listIndices, UINT sizeOfList, RenderSystem* system);
	UINT getSizeIndexList();
	
	~IndexBuffer();

private:
	UINT SizeList;

private:
	ID3D11Buffer* MyBuffer;
	RenderSystem* RSystem = nullptr;

private:
	friend class DeviceContext;
	
};

