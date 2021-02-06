#pragma once
#include "AGameObject.h"
#include "Prerequisites.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "GraphicsEngine.h"
#include "TexturedCube.h"
#include "Bunnyobj.h"
#include "Teapotobj.h"
#include "Statueobj.h"
#include "Cube.h"
#include "Plane.h"
#include "PhysicsCube.h"
#include <iostream>

class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	enum PrimitiveType {
		TEXTUREDCUBE,
		PHYSICS_CUBE,
		CUBE,
		PLANE,
		SPHERE,
		BUNNY,
		TEAPOT,
		STATUE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(String name);
	List getAllObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(String name);
	void setSelectedObject(String name);
	void setSelectedObject(AGameObject* name);
	AGameObject* getSelectedObject();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};

	static GameObjectManager* sharedInstance;
	AGameObject* SelectedObject = NULL;

	List GameObjectList;
	HashTable GameObjectTable;
};

