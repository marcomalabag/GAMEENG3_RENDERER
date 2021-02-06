#pragma once
#include <d3d11.h>
#include "VertexBufferWithoutTexture.h"
#include "Prerequisites.h"

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader, RenderSystem* system);
	virtual UINT getSizeVertexList();
	~VertexBuffer();

protected:
	UINT m_size_vertex;
	UINT m_size_list;

	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	RenderSystem* RSystem = nullptr;
private:
	friend class DeviceContext;
};

