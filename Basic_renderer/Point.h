#pragma once
class Point
{
public:
	Point();
	Point(int x, int y);
	Point(const Point& point);
	~Point();
	int getX();
	int getY();
	void setZeroes();
	

public:
	int x = 0;
	int y = 0;
};

