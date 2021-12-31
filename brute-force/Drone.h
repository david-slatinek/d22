#ifndef DRONE
#define DRONE

#include <string>
#include <vector>
#include <iostream>

#include "Point.h"

using namespace std;

class Drone
{
private:
    Point startPosition;
    Point endPosition;
    Point currentPosition;
    vector <Point*> allCoordinates;
    vector <Point> pathToEnd;

    int index;
    bool end;
public:
    Drone();
    Drone(Point startPos, Point endPos, std::vector<Point*> allPos);
    Drone(Point startPos, Point endPos);
    //virtual ~Drone();

    Point getCurrentPosition() const;
    int getIndex() const;
    bool isNext() const;
    bool isEnd() const;
    Point getNext();
    Point getPrev();

    void addCoordinate(Point* coordinate);
    void setCurrentPosition(Point currentPosition);
    void setIndex(int index);
    void setEnd(bool end);
    void addAll(vector<Point*> allPos);
    bool goBack(Point current);

    void addToPath(Point p);
    int getPathSize();
    Point getCoordinate(int i);

    //virtual std::string toString() const;
};

#endif
