#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#include "Drone.h"
#include "Point.h"

using namespace std;

void generateCoordinates(int start, const int end, int a[])
{
    int counter = 0;
    while (start != end)
    {
        a[counter++] = start;
        if (start < end)
            start++;
        else
            start--;
    }
    a[counter] = start;
}


bool pathOK(Point a, Point b){
    return a.getX() != b.getX() && a.getY() != b.getY() && a.getZ() != b.getZ();
}

void dronesPath(Drone A, Drone B){


}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "Uporaba: ./main [datoteka]" << endl;
        exit(1);
    }

    ifstream file(argv[1], ios::in);
    if (!file.is_open())
    {
        cerr << "Napaka: datoteke ni bilo mogoče odpreti." << endl;
        exit(1);
    }

    int start_a[3], end_a[3];
    int start_b[3], end_b[3];

    file >> start_a[0] >> start_a[1] >> start_a[2];
    file >> end_a[0] >> end_a[1] >> end_a[2];

    file >> start_b[0] >> start_b[1] >> start_b[2];
    file >> end_b[0] >> end_b[1] >> end_b[2];

    file.close();

    // generate all coordnates for A
    int maxSizeA = INT_MIN;
    int cSizeX = abs(start_a[0] - end_a[0]) + 1;
    if (cSizeX > maxSizeA)
        maxSizeA = cSizeX;
    int coordinatesXA[cSizeX];
    generateCoordinates(start_a[0], end_a[0], coordinatesXA);

    int cSizeY = abs(start_a[1] - end_a[1]) + 1;
    if (cSizeY > maxSizeA)
        maxSizeA = cSizeY;
    int coordinatesYA[cSizeY];
    generateCoordinates(start_a[1], end_a[1], coordinatesYA);

    int cSizeZ = abs(start_a[2] - end_a[2]) + 1;
    if (cSizeZ > maxSizeA)
        maxSizeA = cSizeZ;
    int coordinatesZA[cSizeZ];
    generateCoordinates(start_a[2], end_a[2], coordinatesZA);


    // generate all coordinates for B
    int maxSizeB = INT_MIN;
    cSizeX = abs(start_b[0] - end_b[0]) + 1;
    if (cSizeX > maxSizeB)
        maxSizeB = cSizeX;
    int coordinatesXB[cSizeX];
    generateCoordinates(start_b[0], end_b[0], coordinatesXB);

    cSizeY = abs(start_b[1] - end_b[1]) + 1;
    if (cSizeY > maxSizeB)
        maxSizeB = cSizeY;
    int coordinatesYB[cSizeY];
    generateCoordinates(start_b[1], end_b[1], coordinatesYB);

    cSizeZ = abs(start_b[2] - end_b[2]) + 1;
    if (cSizeZ > maxSizeB)
        maxSizeB = cSizeZ;
    int coordinatesZB[cSizeZ];
    generateCoordinates(start_b[2], end_b[2], coordinatesZB);


    vector<Point *> pointsA;
    for (int i = 0; i < maxSizeA; i++)
        pointsA.push_back(new Point());

    for (int i = 0; i < cSizeX; i++)
        pointsA[i]->setX(coordinatesXA[i]);

    for (int i = 0; i < cSizeY; i++)
        pointsA.at(i)->setY(coordinatesYA[i]);

    for (int i = 0; i < cSizeZ; i++)
        pointsA.at(i)->setZ(coordinatesZA[i]);

    for (size_t i = 0; i < pointsA.size(); i++)
        cout << pointsA.at(i)->toString() << endl;



    vector<Point *> pointsB;
    for (int i = 0; i < maxSizeB; i++)
        pointsB.push_back(new Point());

    for (int i = 0; i < cSizeX; i++)
        pointsB[i]->setX(coordinatesXA[i]);

    for (int i = 0; i < cSizeY; i++)
        pointsB.at(i)->setY(coordinatesYA[i]);

    for (int i = 0; i < cSizeZ; i++)
        pointsB.at(i)->setZ(coordinatesZA[i]);

    for (size_t i = 0; i < pointsB.size(); i++)
        cout << pointsB.at(i)->toString() << endl;



    for (const auto p : pointsB)
        delete p;

    for (const auto p : pointsA)
        delete p;

    return 0;
}
