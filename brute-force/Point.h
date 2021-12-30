#ifndef POINT
#define POINT

#include <string>

using namespace std;

class Point
{
private:
    int x, y, z;

public:
    Point();
    Point(int val[3]);
    virtual ~Point();

    int getX() const;
    int getY() const;
    int getZ() const;

    void setX(int x);
    void setY(int y);
    void setZ(int z);

    virtual string toString() const;
};

#endif