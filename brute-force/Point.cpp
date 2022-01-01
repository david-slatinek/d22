#include "Point.h"

Point::Point() {}

Point::Point(int val[3]) {
    this->x = val[0];
    this->y = val[1];
    this->z = val[2];
}

Point::Point(int x, int y, int z){
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


string Point::toString() const
{
    return std::to_string(getX()) + ":" + std::to_string(getY()) + ":" + std::to_string(getZ()) + "\n";
}

bool Point::isSame(Point a, Point b){
    return a.getX() == b.getX() && a.getY() == b.getY() && a.getZ() == b.getZ();
}
