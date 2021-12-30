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
    bool end;
public:
    Drone();
    virtual ~Drone();

    Point getCurrentPosition() const;
    int getIndex() const;
    bool isNext() const;
    bool isEnd() const;
    Point getNext();

    void addCoordinate(Point coordinate);
    void setCurrentPosition(Point currentPosition);
    void setIndex(int index);
    void setEnd(bool end);

    //virtual std::string toString() const;
};

#endif
