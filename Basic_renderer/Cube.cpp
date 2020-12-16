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



Cube::Cube(string name, void* shaderByteCode, size_t sizeShader):AGameObject(name)
{

	Vertex list[] =
	{
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};



	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(list, sizeof(Vertex), ARRAYSIZE(list), shaderByteCode, sizeShader);

	unsigned int indexlist[] =
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

	this->indexBuffer = GraphicsEngine::get()->createIndexbuffer();
	this->indexBuffer->load(indexlist, ARRAYSIZE(indexlist));

	constant cc;
	cc.m_time = 0;

	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
	this->indexBuffer->release();
	this->vertexBuffer->release();
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	

	if (this->ticks >= 0) {
		this->ticks -= this->deltaTime;
	}
	else {
		this->ticks += this->deltaTime;
	}

	float rotS = this->ticks * 0.5f;

	this->setRotation(rotS, rotS, rotS);
}

void Cube::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader, float rotX, float rotY)
{
	constant cc;
	cc.m_time = this->deltaTime ;
	
	InputSystem::get()->update();

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
		ARatio, ARatio, 0.1f, 100.0f
	);

	this->constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, this->constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, this->constantBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->indexBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vertexBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleListIndexed(this->indexBuffer->getSizeIndexList(), 0, 0);

}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

void Cube::onKeyDown(int key)
{
	if (key == 'W') {
		this->rotX += 3.14 * this->deltaTime;
		std::cout << "W is pressed";
	}

	else if (key == 'S') {
		this->rotX -= 3.14 * this->deltaTime;
		std::cout << "S is pressed";
	}

	else if (key == 'A') {
		this->rotY += 3.14 * this->deltaTime;
		std::cout << "A is pressed";
	}

	else if (key == 'D') {
		this->rotY -= 3.14 * this->deltaTime;
		std::cout << "D is pressed";
	}
}

void Cube::onKeyUp(int key) {

}

void Cube::onMouseMove(const Point& delta_mouse_pos)
{

}

void Cube::onLeftMouseDown(const Point& mouse_pos)
{
}

void Cube::onLeftMouseUp(const Point& mouse_pos)
{
}

void Cube::onRightMouseDown(const Point& mouse_pos)
{
}

void Cube::onRightMouseUp(const Point& mouse_pos)
{
}



