#include "TextureManager.h"
#include "Texture.h"
#include <iostream>

TextureManager::TextureManager() : ResourceManager()
{
}

TextureManager::~TextureManager()
{
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* filePath)
{
    return std::static_pointer_cast<Texture>(createResourceFromFile(filePath));
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* filePath)
{
    Texture* text = nullptr;
    try {
        text = new Texture(filePath);
    }
    catch(...){}
    

    return text;
}
