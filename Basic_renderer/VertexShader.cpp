#include "VertexShader.h"
#include "RenderSystem.h"
#include <exception>


VertexShader::VertexShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system)
{
	this->RSystem = system;

	if (!SUCCEEDED(this->RSystem->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs))) {
		throw std::exception("VertexShader not created successfully");
	}
}


VertexShader::~VertexShader()
{
	m_vs->Release();
}
