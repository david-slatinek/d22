#include "Drone.h"

Drone::Drone() {
    this->end = false;
    this->index = -1;
}
Drone::Drone(Point startPos, Point endPos, std::vector<Point> allPos) {
    this->startPosition = startPos;
    this->endPosition = endPos;
    this->allCoordinates = allPos;

    for (int i = 0; i < (int)allPos.size(); i++)
    {
        this->edges.push_back(vector<bool>(allPos.size(), false));
    }

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
    return allCoordinates[index-1];
}

int Drone::getIndex() const {
    return index;
}
bool Drone::isNext() const {
    return (index + 1) < (int)allCoordinates.size();
}
Point Drone::getNext() {
    return allCoordinates[++index];
}
bool Drone::isEnd() const {
    return end;
}

bool Drone::IsAtEnd() {
    return this->pathToEnd.back() == this->endPosition;
}

void Drone::setCurrentPosition(Point position) {
    currentPosition.setX(position.getX());
    currentPosition.setY(position.getY());
    currentPosition.setZ(position.getZ());

}

void Drone::addAll(vector<Point> allPos){
    allCoordinates = allPos;
}

void Drone::addToPath(Point p) {
    this->pathToEnd.push_back(p);
    this->currentPosition = p;
}

int Drone::getPathSize() {
    return this->pathToEnd.size();
}

Point Drone::getCoordinate(int i) {
    return this->pathToEnd[i];
}

void Drone::GenerateEdges() {
    for (int i = 0; i < (int)allCoordinates.size(); i++) {
        for (int j = i; j < (int)allCoordinates.size(); j++) {
            this->edges[i][j] = true;
        }
    }
}

bool Drone::ValidEdge() {
    auto it = find(this->allCoordinates.begin(), this->allCoordinates.end(), this->pathToEnd.back());
    if (it != allCoordinates.end()) {
        int i = it - allCoordinates.begin();

        return this->edges[index][i];
    }
    return false;
}


void Drone::addCoordinate(Point coordinate){
    allCoordinates.push_back(coordinate);
}

void Drone::setIndex(int index) {
    this->index = index;
}

void Drone::setEnd(bool end) {
    this->end = end;
}
