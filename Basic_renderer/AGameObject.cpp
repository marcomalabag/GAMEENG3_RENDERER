#include "AGameObject.h"
#include "Vector3D.h"

AGameObject::AGameObject()
{
}

AGameObject::AGameObject(String name)
{
	this->name = name;
	Vector3D* temp = new Vector3D;
	this->localRotation = temp->zeros();
	this->localPosition = temp->zeros();
	this->localScale = temp->ones();
	this->localMatrix.setIdentity();
}

AGameObject::~AGameObject()
{
}

AGameObject::String AGameObject::getName() {
	return this->name;
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::findComponentByName(String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}


void AGameObject::awake()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

void AGameObject::setLocalMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4 scaleMatrix; scaleMatrix.setScale(this->localScale);
	Matrix4 transMatrix; transMatrix.setTranslation(this->localPosition);
	this->localMatrix = scaleMatrix.MultiplyMatrix(transMatrix.MultiplyMatrix(newMatrix));
}

float* AGameObject::getPhysicsLocalMatrix()
{
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

	return SumM.getMatrix();
}

void AGameObject::updateLocalMatrix()
{
	Matrix4 allMatrix; allMatrix.setIdentity();
	Matrix4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4 xMatrix; xMatrix.setRotationX(rotation.getX());
	Matrix4 yMatrix; yMatrix.setRotationY(rotation.getY());
	Matrix4 zMatrix; zMatrix.setRotationZ(rotation.getZ());

	Matrix4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.MultiplyMatrix(xMatrix.MultiplyMatrix(yMatrix.MultiplyMatrix(zMatrix)));

	allMatrix = allMatrix.MultiplyMatrix(scaleMatrix.MultiplyMatrix(rotMatrix));
	allMatrix = allMatrix.MultiplyMatrix(translationMatrix);
	this->localMatrix = allMatrix;
}




