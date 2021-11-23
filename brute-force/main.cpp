#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

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

    int maxSizeA = INT_MIN;
    int cSizeX = abs(start_a[0] - end_a[0]) + 1;
    if (cSizeX > maxSizeA)
        maxSizeA = cSizeX;
    int coordinatesX[cSizeX];
    generateCoordinates(start_a[0], end_a[0], coordinatesX);

    int cSizeY = abs(start_a[1] - end_a[1]) + 1;
    if (cSizeY > maxSizeA)
        maxSizeA = cSizeY;
    int coordinatesY[cSizeY];
    generateCoordinates(start_a[1], end_a[1], coordinatesY);

    int cSizeZ = abs(start_a[2] - end_a[2]) + 1;
    if (cSizeZ > maxSizeA)
        maxSizeA = cSizeZ;
    int coordinatesZ[cSizeZ];
    generateCoordinates(start_a[2], end_a[2], coordinatesZ);

    vector<Point *> pointsA;
    for (int i = 0; i < maxSizeA; i++)
        pointsA.push_back(new Point());

    for (int i = 0; i < cSizeX; i++)
        pointsA[i]->setX(coordinatesX[i]);

    for (int i = 0; i < cSizeY; i++)
        pointsA.at(i)->setY(coordinatesY[i]);

    for (int i = 0; i < cSizeZ; i++)
        pointsA.at(i)->setZ(coordinatesZ[i]);

    for (size_t i = 0; i < pointsA.size(); i++)
        cout << pointsA.at(i)->toString() << endl;

    for (const auto p : pointsA)
        delete p;

    return 0;
}