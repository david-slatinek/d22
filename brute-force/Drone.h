#ifndef DRONE
#define DRONE

#include <string>
#include <vector>
#include "Point.h"

class Drone
{
private:
    Point startPosition;
    Point endPosition;
    Point currentPosition;
    std::vector <Point> allCoordinates;
    int index;
public:
    Drone();
    virtual ~Drone();

    Point getCurrentPosition() const;
    int getIndex() const;
    bool isNext() const;
    Point getNext() const;

    void setCurrentPosition(Point CurrentPosition);
    void setIndex(int index);

    //virtual std::string toString() const;
};

#endif
