#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "VertexBuffer.h"


class VertexBufferWithoutTexture
{
public:
	VertexBufferWithoutTexture(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader, RenderSystem* system);
	virtual UINT getSizeVertexList();
	~VertexBufferWithoutTexture();
private:
	UINT m_size_vertex;
	UINT m_size_list;

	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	RenderSystem* RSystem = nullptr;

	friend class DeviceContext;
};

