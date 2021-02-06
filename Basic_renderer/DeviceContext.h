#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class SwapChain;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class IndexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
	void clearRenderTargetColor(SwapChainPtr swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(const VertexBufferPtr vertex_buffer);
	void setVertexBufferWithoutTexture(const VertexBufferWithoutTexturePtr vertex_buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleListIndexed(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);

	void setVertexShader(const VertexShaderPtr vertex_shader);
	void setPixelShader(const PixelShaderPtr pixel_shader);

	void setConstantBuffer(const VertexShaderPtr vertex_shader, const ConstantBufferPtr buffer);
	void setConstantBuffer(const PixelShaderPtr pixel_shader, const ConstantBufferPtr buffer);

	void setTexture(const VertexShaderPtr vertex_shader, const TexturePtr texture);
	void setTexture(const PixelShaderPtr pixel_shader, const TexturePtr texture);

	void setIndexBuffer(const IndexBufferPtr index_buffer);

	
	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
	RenderSystem* RSystem = nullptr;

private:
	friend class ConstantBuffer;
	friend class Texture;
	
};



