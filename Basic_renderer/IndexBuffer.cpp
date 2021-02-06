#include "IndexBuffer.h"
#include "RenderSystem.h"
#include <exception>

IndexBuffer::IndexBuffer(void* listIndices, UINT sizeOfList, RenderSystem* system)  {

    this->MyBuffer = 0;
    this->RSystem = system;

    D3D11_BUFFER_DESC BuffDesc = {};
    BuffDesc.Usage = D3D11_USAGE_DEFAULT;
    BuffDesc.ByteWidth = 4 * sizeOfList;
    BuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    BuffDesc.CPUAccessFlags = 0;
    BuffDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initializaData = {};
    initializaData.pSysMem = listIndices;

    this->SizeList = sizeOfList;

    if (FAILED(this->RSystem->m_d3d_device->CreateBuffer(&BuffDesc, &initializaData, &MyBuffer))) {
        throw std::exception("IndexBuffer not created successfully");
    }
}


UINT IndexBuffer::getSizeIndexList()
{
    return this->SizeList;
}

IndexBuffer::~IndexBuffer()
{
    MyBuffer->Release();
}
