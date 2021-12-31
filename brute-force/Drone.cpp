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

// vrnemo true, če je bil premik mogoč
bool Drone::goBack(Point current){
    // dodamo na pot prejšno in spremenimo index na prejšno

    // če dron ne miruje se premknemo nazaj, sicer še ne vem kaj bi
    if(!Point::isSame(current, pathToEnd[getPathSize()-1])){
        addToPath(pathToEnd[getPathSize()-1]);
        setCurrentPosition(pathToEnd[getPathSize()-1]);
        index--;
        return true;
    }
    return false;

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
    setCurrentPosition(pathToEnd[getPathSize()-1]);

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
