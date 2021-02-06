#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4.h"
#include <vector>
#include "AComponent.h"
#include "reactphysics3d/reactphysics3d.h"

using namespace reactphysics3d;


class GameObjectManager;
class VertexShader;
class PixelShader;
class AComponent;
class AGameObject
{
public:
	struct AQuaternion {
		float w = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	__declspec(align(16))
	struct constant
	{
		Matrix4 m_world;
		Matrix4 m_view;
		Matrix4 m_proj;
		float m_angle = 0.0;
		unsigned int m_time = 0;
	};

	typedef std::string String;
	typedef std::vector<AComponent*> ComponentList;
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3 };

	AGameObject();
	AGameObject(String name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int with, int height) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	void setLocalMatrix(float matrix[16]);
	float* getPhysicsLocalMatrix();
	void updateLocalMatrix();

	String getName();
	friend class GameObjectManager;

	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(String name);

	

protected:
	String name;
	Vector3D localRotation;
	Vector3D localPosition;
	Vector3D localScale;
	AQuaternion orientation;
	Matrix4 localMatrix;

	ComponentList componentList;

	bool overrideMatrix = false;

	virtual void awake();
};


