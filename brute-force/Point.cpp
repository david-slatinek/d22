#include "Point.h"

Point::Point() {}

Point::Point(int val[3]) {
    this->x = val[0];
    this->y = val[1];
    this->z = val[2];
}

Point::~Point() {}

int Point::getX() const { return x; }
int Point::getY() const { return y; }
int Point::getZ() const { return z; }

void Point::setX(int x) { this->x = x; }
void Point::setY(int y) { this->y = y; }
void Point::setZ(int z) { this->z = z; }

string Point::toString() const
{
    char* buff = new char[32];
    sprintf_s(buff, 32, "(%d %d %d)", x, y, z);
    return buff;
}

bool operator==(Point p1, Point p2) {
    return p1.getX() == p2.getX() && p1.getY() == p2.getY() && p1.getZ() == p2.getZ();
}
