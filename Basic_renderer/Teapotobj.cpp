#include "Teapotobj.h"
#include "SwapChain.h"
#include "GraphicsEngine.h"
#include <Windows.h>
#include "Vector3D.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "AppWindow.h"
#include "EngineTime.h"
#include "Matrix4.h"
#include "InputSystem.h"
#include "Vector2D.h"
#include <iostream>
#include "Mesh.h"

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

Teapotobj::Teapotobj(String name, void* shaderByteCode, size_t sizeShader):AGameObject(name)
{
	this->MyMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
	this->Text = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
	

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	constant cc;
	cc.m_time = 0;

	ShaderNames names;
	ShaderLibrary::getInstance()->requestVertexShaderData(names.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	this->constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(names.TEXTURED_VERTEX_SHADER_NAME));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(names.TEXTURED_PIXEL_SHADER_NAME));
}

Teapotobj::~Teapotobj()
{
	AGameObject::~AGameObject();
}

void Teapotobj::update(float deltaTime)
{
	this->deltaTime = deltaTime;


	if (InputSystem::getInstance()->isKeyDown('W')) {
		this->ticks += this->deltaTime;
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		this->ticks -= this->deltaTime;
	}


	float rotS = this->ticks * this->speed;

	this->setScale(rotS, rotS, rotS);
}

void Teapotobj::draw(int width, int height)
{
	constant cc;
	cc.m_time = this->deltaTime;


	if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}
	else {
		this->deltaPos += this->deltaTime * 0.4f;
	}

	Vector3D rot;


	Matrix4 SumM;
	Matrix4 translate;
	Matrix4 Scale;

	Matrix4 rotZ;
	Matrix4 rotF;
	Matrix4 rotGl;

	Matrix4 rotM;


	SumM.setIdentity();
	Scale.setIdentity();
	translate.setTranslation(this->getLocalPosition());
	Scale.setScale(this->getLocalScale());
	rot = Vector3D(this->getLocalRotation());

	rotZ.setIdentity();
	rotZ.setRotationZ(rot.getZ());

	rotF.setIdentity();
	rotF.setRotationX(rot.getX());

	rotGl.setIdentity();
	rotGl.setRotationY(rot.getY());



	rotM.setIdentity();

	rotM = rotM.MultiplyMatrix(rotF.MultiplyMatrix(rotGl.MultiplyMatrix(rotZ)));
	SumM = SumM.MultiplyMatrix(Scale.MultiplyMatrix(rotM));
	SumM = SumM.MultiplyMatrix(translate);
	cc.m_world = SumM;

	Matrix4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

	float ARatio = (float)width / (float)height;

	cc.m_proj.setPerspectiveFovLH
	(
		1.57f, ARatio, 0.1f, 100.0f
	);

	ShaderNames names;
	this->constantBuffer->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(names.TEXTURED_VERTEX_SHADER_NAME), this->constantBuffer);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(names.TEXTURED_PIXEL_SHADER_NAME), this->constantBuffer);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(ShaderLibrary::getInstance()->getPixelShader(names.TEXTURED_PIXEL_SHADER_NAME), this->Text);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(this->MyMesh->getIndexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(this->MyMesh->getVertexBuffer());

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawTriangleListIndexed(this->MyMesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
}

void Teapotobj::setAnimSpeed(float speed)
{
	this->speed = speed;
}
