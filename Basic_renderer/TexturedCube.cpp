#include "TexturedCube.h"
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


TexturedCube::TexturedCube(String name, void* shaderByteCode, size_t sizeShader):AGameObject(name)
{
	std::cout << "Textured cube created" << "\n";
	this->MyMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
	this->WoodTxt = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
	
	ShaderNames names;
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(names.TEXTURED_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);

	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};



	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }


	};
	
	if (shader_byte_code == NULL) {
		std::cout << "NULL" << "\n";
	}
	this->vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shader_byte_code, (UINT)size_shader);
	if (this->vertexBuffer == NULL) {
		std::cout << "NUll" << "\n";
	}

	unsigned int indexlist[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	this->indexBuffer = GraphicsEngine::get()->getRenderSystem()->createIndexbuffer(indexlist, ARRAYSIZE(indexlist));

	constant cc;
	cc.m_time = 0;

	this->constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(names.TEXTURED_VERTEX_SHADER_NAME));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(names.TEXTURED_PIXEL_SHADER_NAME));
}

TexturedCube::~TexturedCube()
{
	
	AGameObject::~AGameObject();
}

void TexturedCube::update(float deltaTime)
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

void TexturedCube::draw(int width, int height)
{
	constant cc;
	cc.m_time = this->deltaTime ;
	

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
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(names.TEXTURED_VERTEX_SHADER_NAME) , this->constantBuffer);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(names.TEXTURED_PIXEL_SHADER_NAME), this->constantBuffer);
	
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(ShaderLibrary::getInstance()->getPixelShader(names.TEXTURED_PIXEL_SHADER_NAME), this->WoodTxt);
	

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(this->indexBuffer);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(this->vertexBuffer);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawTriangleListIndexed(this->indexBuffer->getSizeIndexList(), 0, 0);

}

void TexturedCube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

