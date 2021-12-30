#include "Drone.h"

Drone::Drone() {}
Drone::~Drone() {}

Point Drone::getCurrentPosition() const { return currentPosition; }
int Drone::getIndex() const { return index; }
bool Drone::isNext() const { return !(index+1<allCoordinates.size()); }
Point Drone::getNext() const { return allCoordinates[index+1]; }


void Drone::setCurrentPosition(Point position) {
    currentPosition.setX(position.getX());
    currentPosition.setY(position.getY());
    currentPosition.setZ(position.getZ());

}

void Drone::setIndex(int index) { this->index = index; }
