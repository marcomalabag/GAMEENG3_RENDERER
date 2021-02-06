#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "Point.h"
#include "SceneCameraHandler.h"
#include <iostream>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Prerequisites.h"
#include "ShaderLibrary.h"
#include "ShaderNames.h"
#include "GraphicsEngine.h"

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class Plane: public AGameObject
{
public:

	Plane(String name, void* shaderByteCode, size_t sizeShader);
	~Plane();

	void update(float deltaTime) override;
	void draw(int width, int height);
	void setAnimSpeed(float speed);

private:
	VertexBufferWithoutTexturePtr vertexBuffer;
	IndexBufferPtr indexBuffer;
	ConstantBufferPtr constantBuffer;
	TexturePtr WoodTxt;
	MeshPtr MyMesh;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
	float deltaScale = 0.0f;
	float deltaRotation = 0.0f;

	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;
};

