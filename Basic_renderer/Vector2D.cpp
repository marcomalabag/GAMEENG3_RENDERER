#include "Vector2D.h"

Vector2D::Vector2D()
{
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D(const Vector2D& vector)
{
	this->x = vector.x;
	this->y = vector.y;
}

Vector2D Vector2D::operator*(float num)
{
	return Vector2D(this->x * num, this->y * num);
}

Vector2D Vector2D::operator+(Vector2D vector)
{
	return Vector2D(this->x + vector.x, this->y + vector.y);
}

Vector2D::~Vector2D()
{
}
