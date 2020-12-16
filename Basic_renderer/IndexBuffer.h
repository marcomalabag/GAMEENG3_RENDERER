#pragma once
#include <d3d11.h>

class IndexBuffer
{
public:
	IndexBuffer();
	bool load(void* listIndices, UINT sizeOfList);
	UINT getSizeIndexList();
	bool release();
	~IndexBuffer();

private:
	UINT SizeList;

private:
	ID3D11Buffer* MyBuffer;


private:
	friend class DeviceContext;
	friend class GraphicsEngine;
};

