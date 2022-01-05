#include "Drone.h"

Drone::Drone()
{
	this->end = false;
	this->index = -1;
}

Drone::Drone(Point startPos, Point endPos, std::vector<Point> allPos)
{
	this->startPosition = startPos;
	this->endPosition = endPos;
	this->allCoordinates = allPos;

	for (int i = 0; i < (int)allPos.size(); i++)
	{
		this->edges.push_back(vector<bool>(allPos.size(), false));
	}

	index = -1;
}

Drone::Drone(Point startPos, Point endPos)
{
	this->startPosition = startPos;
	this->endPosition = endPos;
	index = -1;
}

Point Drone::getCurrentPosition() const
{
	return currentPosition;
}

Point Drone::getStartPosition() const
{
	return this->startPosition;
}

Point Drone::getEndPosition() const
{
	return this->endPosition;
}

Point Drone::getPrev()
{
	return allCoordinates[index - 1];
}

int Drone::getIndex() const
{
	return index;
}

bool Drone::isNext() const
{
	return (index + 1) < (int)allCoordinates.size();
}

Point Drone::getNext()
{
	return allCoordinates[++index];
}

bool Drone::isEnd() const
{
	return end;
}

bool Drone::IsAtEnd()
{
	return this->pathToEnd.back() == this->endPosition;
}

std::string Drone::toString() const
{
	string start = "Start: (" + to_string(startPosition.getX()) + " " + to_string(startPosition.getY()) + " " + to_string(startPosition.getZ()) + ")";
	string end = "End: (" + to_string(endPosition.getX()) + " " + to_string(endPosition.getY()) + " " + to_string(endPosition.getZ()) + ")";

	return start + "  " + end;
}

void Drone::setCurrentPosition(Point position)
{
	currentPosition.setX(position.getX());
	currentPosition.setY(position.getY());
	currentPosition.setZ(position.getZ());
}

void Drone::backtrack(Point p)
{
	// če bi premik nazaj pomenil, da bi se premaknili na enako pozicijo
	if (p == currentPosition)
	{
		cout << "Ne vem kaj storiti" << endl;
	}
	else
	{
		index--;
		addToPath(pathToEnd[getPathSize() - 1]);
	}
}

void Drone::addAll(vector<Point> allPos)
{
	allCoordinates = allPos;
}

void Drone::addToPath(Point p)
{
	this->pathToEnd.push_back(p);
	this->currentPosition = p;
}

int Drone::getPathSize()
{
	return this->pathToEnd.size();
}

Point Drone::getCoordinate(int i)
{
	if (i >= pathToEnd.size())
		return Point();
	else
		return this->pathToEnd[i];
}

bool Drone::IsHovering()
{
	if (pathToEnd.size() > 1)
	{
		return this->pathToEnd.back() == this->pathToEnd.at(this->pathToEnd.size() - 2);
	}
	else
	{
		return false;
	}
}

void Drone::GenerateEdges()
{
	for (int i = 0; i < (int)allCoordinates.size(); i++)
	{
		for (int j = i; j < (int)allCoordinates.size(); j++)
		{
			this->edges[i][j] = true;
		}
	}
}

bool Drone::ValidEdge(Point p)
{
	if (abs(p.getX() - currentPosition.getX()) <= 1 && abs(p.getY() - currentPosition.getY()) <= 1 && abs(p.getZ() - currentPosition.getZ()) <= 1)
	{
		int sum = abs(p.getX() - currentPosition.getX()) + abs(p.getY() - currentPosition.getY()) + abs(p.getZ() - currentPosition.getZ());
		return sum <= 1;
	}
	else
		return false;
}

void Drone::removeCoordinateAt(int i)
{
	pathToEnd.erase(pathToEnd.begin() + i);
}

void Drone::addToPathAtIndex(int i, Point p)
{
	if (i >= pathToEnd.size())
	{
		pathToEnd.push_back(p);
	}
	else
	{
		pathToEnd.insert(pathToEnd.begin() + i, p);
	}
}

void Drone::addCoordinate(Point coordinate)
{
	allCoordinates.push_back(coordinate);
}

void Drone::setIndex(int index)
{
	this->index = index;
}

void Drone::setEnd(bool end)
{
	this->end = end;
}
