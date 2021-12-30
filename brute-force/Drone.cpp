#include "Drone.h"

Drone::Drone() {
    end = false;
}
Drone::Drone(Point startPos, Point endPos, vector<Point*> allPos) {
    this->startPosition = startPos;
    this->endPosition = endPos;
    this->allCoordinates = allPos;
    index = -1;
}

Drone::~Drone() {}

Point Drone::getCurrentPosition() const { 
    return currentPosition; 
}
int Drone::getIndex() const { 
    return index; 
}
bool Drone::isNext() const { 
    return index+1<allCoordinates.size(); 
}
Point Drone::getNext() { 
    return *allCoordinates[++index]; 
}
bool Drone::isEnd() const { 
    return end; 
}



void Drone::setCurrentPosition(Point position) {
    currentPosition.setX(position.getX());
    currentPosition.setY(position.getY());
    currentPosition.setZ(position.getZ());

}

void Drone::addCoordinate(Point* coordinate){
    allCoordinates.push_back(coordinate);
}

void Drone::setIndex(int index) { 
    this->index = index; 
}

void Drone::setEnd(bool end) { 
    this->end = end; 
}
