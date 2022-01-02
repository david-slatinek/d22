#include "Point.h"

Point::Point() {}

Point::Point(int val[3]) {
	this->x = val[0];
	this->y = val[1];
	this->z = val[2];
}
Point::Point(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::~Point() {}

int Point::getX() const { return x; }
int Point::getY() const { return y; }
int Point::getZ() const { return z; }

void Point::setX(int x) { this->x = x; }
void Point::setY(int y) { this->y = y; }
void Point::setZ(int z) { this->z = z; }

string Point::toString() const {
	//return "[" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + "]";  // za Blender test
	return "(" + to_string(x) + " " + to_string(y) + " " + to_string(z) + ")";
}

bool operator==(Point p1, Point p2) {
	return p1.getX() == p2.getX() && p1.getY() == p2.getY() && p1.getZ() == p2.getZ();
}
