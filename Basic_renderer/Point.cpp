#include "Point.h"

Point::Point()
{
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::Point(const Point & point)
{
	this->x = point.x;
	this->y = point.y;
	
}

Point::~Point()
{
}

int Point::getX()
{
	return this->x;
}

int Point::getY()
{
	return this->y;
}

void Point::setZeroes()
{
	this->x = 0;
	this->y = 0;
}
