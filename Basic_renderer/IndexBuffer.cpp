#include "IndexBuffer.h"
#include "GraphicsEngine.h"

IndexBuffer::IndexBuffer() : MyBuffer(0) {

}

bool IndexBuffer::load(void* listIndices, UINT sizeOfList)
{
    if (MyBuffer)MyBuffer->Release();

    D3D11_BUFFER_DESC BuffDesc = {};
    BuffDesc.Usage = D3D11_USAGE_DEFAULT;
    BuffDesc.ByteWidth = 4 * sizeOfList;
    BuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    BuffDesc.CPUAccessFlags = 0;
    BuffDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initializaData = {};
    initializaData.pSysMem = listIndices;

    SizeList = sizeOfList;

    if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&BuffDesc, &initializaData, &MyBuffer))) {
        return false;
    }

    return true;
}

UINT IndexBuffer::getSizeIndexList()
{
    return this->SizeList;
}

bool IndexBuffer::release()
{
    MyBuffer->Release();
    delete this;
    return false;
}

IndexBuffer::~IndexBuffer()
{
}
