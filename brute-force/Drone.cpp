#include "Drone.h"

Drone::Drone() {
    end = false;
}
Drone::Drone(Point startPos, Point endPos, std::vector<Point*> allPos) {
    this->startPosition = startPos;
    this->endPosition = endPos;
    this->allCoordinates = allPos;
    index = -1;
}

Drone::Drone(Point startPos, Point endPos) {
    this->startPosition = startPos;
    this->endPosition = endPos;
    // this->allCoordinates = allPos;
    index = -1;
}
//Drone::~Drone() {}

Point Drone::getCurrentPosition() const {
    return currentPosition;
}

Point Drone::getPrev(){
    return *allCoordinates[index-1];
}

int Drone::getIndex() const {
    return index;
}
bool Drone::isNext() const {
    return (index+1)<allCoordinates.size();
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

void Drone::addAll(vector<Point*> allPos){
    allCoordinates = allPos;
}

void Drone::addToPath(Point p) {
    this->pathToEnd.push_back(p);
}

int Drone::getPathSize() {
    return this->pathToEnd.size();
}

Point Drone::getCoordinate(int i) {
    return this->pathToEnd[i];
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
