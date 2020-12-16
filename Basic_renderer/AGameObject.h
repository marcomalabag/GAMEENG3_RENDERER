#pragma once
#include<string>
#include "Vector3D.h"
#include "Matrix4.h"

using namespace std;

class VertexShader;
class PixelShader;
class AGameObject
{
public:
	AGameObject();
	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int with, int height, VertexShader* vertexShader, PixelShader* pixelShader, float rotX, float rotY) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();




protected:
	string name;
	Vector3D localRotation;
	Vector3D localPosition;
	Vector3D localScale;
	Matrix4 localMatrix;
};

struct Vertex {
	Vector3D position;
	Vector3D color;
	Vector3D color1;
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

