#include "GameObjectManager.h"
#include <vector>
#include "TexturedCube.h"


GameObjectManager* GameObjectManager::sharedInstance = NULL;


GameObjectManager* GameObjectManager::getInstance()
{
    return sharedInstance;
}

void GameObjectManager::initialize()
{
    sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
    sharedInstance->GameObjectList.clear();
    sharedInstance->GameObjectTable.clear();
    delete sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(String name)
{
    if (this->GameObjectTable[name] != NULL) {
        return this->GameObjectTable[name];
    }

    else {
        std::cout << "Game Object does not exist" << '\n';
    }
    return nullptr;
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
    return this->GameObjectList;
}

int GameObjectManager::activeObjects()
{
    return this->GameObjectList.size();
}

void GameObjectManager::updateAll()
{
    for (int i = 0; i < this->GameObjectList.size(); i++) {

        this->GameObjectList[i]->update(EngineTime::getInstance()->getDeltaTime());
    }
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight)
{
    for (int i = 0; i < this->GameObjectList.size(); i++) {
        
        this->GameObjectList[i]->draw(viewportWidth, viewportHeight);
    }
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
    this->GameObjectTable[gameObject->getName()] = gameObject;
    this->GameObjectList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
    
    if (type == PrimitiveType::TEXTUREDCUBE) {
        TexturedCube* texturedcube = new TexturedCube("TexturedCube", shaderByteCode, sizeShader);
        texturedcube->setPosition(0.0f, 0.0f, 0.0f);
        texturedcube->setScale(1.0f, 1.0f, 1.0f);
        this->addObject(texturedcube);
    }

    else if (type == PrimitiveType::CUBE) {
        Cube* cube = new Cube("Cube", shaderByteCode, sizeShader);
        cube->setPosition(0.0f, 1.0f, 0.0f);
        cube->setScale(1.0f, 1.0f, 1.0f);
        this->addObject(cube);
    }

    else if (type == PrimitiveType::BUNNY) {
        Bunnyobj* bunny = new Bunnyobj("Bunny", shaderByteCode, sizeShader);
        bunny->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
        bunny->setScale(Vector3D(1.5f, 1.5f, 1.5f));
        this->addObject(bunny);
    }

    else if (type == PrimitiveType::TEAPOT) {
        Teapotobj* teapot = new Teapotobj("Teapot", shaderByteCode, sizeShader);
        teapot->setPosition(Vector3D(-1.0f, 0.0f, 0.0f));
        teapot->setScale(Vector3D(2.5f, 2.5f, 2.5f));
        this->addObject(teapot);
    }

    else if (type == PrimitiveType::STATUE) {
        Statueobj* statue = new Statueobj("Statue", shaderByteCode, sizeShader);
        statue->setPosition(Vector3D(1.0f, 0.0f, 0.0f));
        statue->setScale(Vector3D(1.5f, 1.5f, 1.5f));
        this->addObject(statue);
    }

    else if (type == PrimitiveType::PLANE) {
        Plane* plane = new Plane("Plane", shaderByteCode, sizeShader);
        plane->setPosition(Vector3D(1.0f, 0.0f, 0.0f));
        plane->setScale(Vector3D(1.5f, 0.1f, 1.0f));
        this->addObject(plane);
    }

    else if (type == PrimitiveType::PHYSICS_CUBE) {
        PhysicsCube* phycube = new PhysicsCube("Cube_Physics");
        this->addObject(phycube);
    }
    

}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
    this->GameObjectTable.erase(gameObject->getName());


    delete gameObject;
}

void GameObjectManager::deleteObjectByName(String name)
{
    if (this->GameObjectTable[name] != NULL) {
        this->deleteObject(this->GameObjectTable[name]);
    }
}

void GameObjectManager::setSelectedObject(String name)
{
    if (this->GameObjectTable[name] != NULL) {
        this->setSelectedObject(this->GameObjectTable[name]);
    }
}

void GameObjectManager::setSelectedObject(AGameObject* name)
{
    this->SelectedObject = name;
}

AGameObject* GameObjectManager::getSelectedObject()
{
    return this->SelectedObject;
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}
