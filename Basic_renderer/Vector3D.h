#pragma once

class Vector3D
{
public:
	Vector3D()
	{
		this->m_x = 0;
		this->m_y = 0;
		this->m_z = 0;
	}
	Vector3D(float x, float y, float z)
	{
		this->m_x = x;
		this->m_y = y;
		this->m_z = z;
	}

	float getX() {
		return m_x;
	}

	float getY() {
		return m_y;
	}

	float getZ() {
		return m_z;
	}

	Vector3D(const Vector3D& vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
	{
	}

	Vector3D zeros() {
		return Vector3D(0, 0, 0);
	}

	Vector3D ones() {
		return Vector3D(1, 1, 1);
	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
		v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
		v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);
		return v;
	}

	Vector3D operator *(float num)
	{
		return Vector3D(m_x * num, m_y * num, m_z * num);
	}

	Vector3D operator +(Vector3D vec)
	{
		return Vector3D(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	~Vector3D()
	{
	}

public:
	float m_x, m_y, m_z;
};