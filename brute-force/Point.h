#ifndef POINT
#define POINT

#include <string>

class Point
{
private:
    int x, y, z;

public:
    Point();
    virtual ~Point();

    int getX() const;
    int getY() const;
    int getZ() const;

    void setX(int x);
    void setY(int y);
    void setZ(int z);

    virtual std::string toString() const;
};

#endif