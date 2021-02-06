#include "Cube.h"
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

struct Vertex {
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

Cube::Cube(String name, void* shaderByteCode, size_t sizeShader):AGameObject(name)
{
	ShaderNames names;
	void* shader_byte_code = NULL;
	size_t size_shader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(names.BASE_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);
	

	Vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,1,1),  Vector3D(0.0f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,1), Vector3D(0.0f,0.0f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,1),  Vector3D(0.0f,0.0f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,1,1), Vector3D(0.0f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(1,1,1), Vector3D(0,0.0f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(1,1,1), Vector3D(0,0.0f,0.0f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(1,1,1),  Vector3D(0,0.0f,0.0f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1,1,1), Vector3D(0,0.0f,0) }

	};

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	this->indexBuffer = GraphicsEngine::get()->getRenderSystem()->createIndexbuffer(index_list, ARRAYSIZE(index_list));
	
	if (shader_byte_code == NULL) {
		std::cout << "Shader Byte Code NULL" << "\n";
	}
	if (size_shader == 0) {
		std::cout << "Size Shader NULL" << "\n";
	}
	
	this->vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBufferWithoutTexture(vertex_list, sizeof(Vertex), ARRAYSIZE(vertex_list), shader_byte_code, size_shader);
	
	
	constant cc;
	cc.m_time = 0;

	
	this->constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(names.BASE_VERTEX_SHADER_NAME));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(names.BASE_PIXEL_SHADER_NAME));
}

Cube::~Cube()
{
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;


	if (InputSystem::getInstance()->isKeyDown('W')) {
		this->ticks -= this->deltaTime;
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		this->ticks += this->deltaTime;
	}


	float rotS = this->ticks * this->speed;

	this->setRotation(rotS, rotS, rotS);
}

void Cube::draw(int width, int height)
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
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(names.BASE_VERTEX_SHADER_NAME), this->constantBuffer);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(names.BASE_PIXEL_SHADER_NAME), this->constantBuffer);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(this->indexBuffer);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBufferWithoutTexture(this->vertexBuffer);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawTriangleListIndexed(this->indexBuffer->getSizeIndexList(), 0, 0);


}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
