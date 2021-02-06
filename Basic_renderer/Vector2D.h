#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& vector);
	Vector2D operator*(float num);
	Vector2D operator+(Vector2D vector);
	~Vector2D();

public:
	float x, y;
};

