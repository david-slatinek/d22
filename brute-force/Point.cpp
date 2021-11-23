#include "Point.h"

Point::Point() {}
Point::~Point() {}

int Point::getX() const { return x; }
int Point::getY() const { return y; }
int Point::getZ() const { return z; }

void Point::setX(int x) { this->x = x; }
void Point::setY(int y) { this->y = y; }
void Point::setZ(int z) { this->z = z; }

std::string Point::toString() const
{
    return std::to_string(getX()) + ":" + std::to_string(getY()) + ":" + std::to_string(getZ()) + "\n";
}