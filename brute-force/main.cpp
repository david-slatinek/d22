#include <iostream>
#include <fstream>
#include <vector>
#include "Drone.h"
#include "Point.h"

using namespace std;
void generateCoordinates(int start, const int end, vector<int> &a)
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
	a.at(counter) = start;
}

// treba je preveriti še da ne pride do križanja, če pride potem ni OK
bool pathOK(Point a, Point b) {

    // vsaj ena izmed koordinat mora biti različna
    if(a.getX() != b.getX())
        return true;
    if(a.getY() != b.getY())
        return true;
    if(a.getZ() != b.getZ())
        return true;
    return false;
}

bool pointsOK(Point a, Point b, Point prevA, Point prevB)
{
    if(Point::isSame(b, prevA) && Point::isSame(a, prevB))
        return false;
        // vsaj ena izmed koordinat mora biti različna
    if(a.getX() != b.getX())
        return true;
    if(a.getY() != b.getY())
        return true;
    if(a.getZ() != b.getZ())
        return true;
    return false;
}

void dronesPath(Drone A, Drone B) {

	Point a = A.getNext();
	Point b = B.getNext();

	// accept starting points
	A.addToPath(a);
	B.addToPath(b);


    // potrebno je preverit še če se točka od trenutne razlikuje za 1
	while (true) {
		if (A.isNext()) {
			a = A.getNext();
		}
		else {
			A.setEnd(true);
		}
		if (B.isNext()) {
			b = B.getNext();
		}
		else {
			B.setEnd(true);
		}
		if (A.isEnd() && B.isEnd()) {
			break;
		}

		if (pointsOK(a, b, A.getCurrentPosition(), B.getCurrentPosition())) {		// TODO - tole mal hecn deluje oz. ne deluje ...
		// if (pathOK(a, b) ) {		// TODO - tole mal hecn deluje oz. ne deluje ...
			A.setCurrentPosition(a);
            B.setCurrentPosition(b);

			A.addToPath(a);
			B.addToPath(b);
		}
		else {
			// TODO - A - umik, B nadaljuje
            // A v bistvu ostane na istem kot je, razen če je trenutni enak kot prvi
            cout<<"Grem nazaj"<<endl;

            // če smo lahko prejšni dron premaknili, potem tega premaknemo na naslednjo
            if(A.goBack(a)){
                // premaknemo se z B dronom, ker smo A umaknili
                B.addToPath(b);

                // če je možno B še za eno pozicijo premaknemo naprej
                // if(B.isNext()){
                //     B.addToPath(B.getNext());
                //     A.addToPath(A.getCurrentPosition());
                // }

            }
            // else{
            //     A.addToPath(Point(A.getCurrentPosition().getX(), A.getCurrentPosition().getY()-1, A.getCurrentPosition().getZ()));
            //     B.addToPath(B.getNext());
            //     if(B.isNext()){
            //         B.addToPath(B.getNext());
            //         A.addToPath(Point(A.getCurrentPosition().getX(), A.getCurrentPosition().getY()+1, A.getCurrentPosition().getZ()));
            //     }
            // }


		}

	}

	std::cout << endl << "Rezultat" << endl;
	cout << "------------------------" << endl;
	int ia = 0, ib = 0;
	for (size_t i = 0; i < min(A.getPathSize(), B.getPathSize()); i++)
	{
		cout << A.getCoordinate(ia).toString() << " " << B.getCoordinate(ib).toString() << "\n";

		if (ia + 1 < A.getPathSize()) ia++;
		if (ib + 1 < B.getPathSize()) ib++;
	}
}

int main(int argc, char* argv[])
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

	// read input
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
	vector<int> coordinatesXA(cSizeX, 0);
	generateCoordinates(start_a[0], end_a[0], coordinatesXA);

	int cSizeY = abs(start_a[1] - end_a[1]) + 1;
	if (cSizeY > maxSizeA)
		maxSizeA = cSizeY;
	vector<int> coordinatesYA(cSizeY, 0);
	generateCoordinates(start_a[1], end_a[1], coordinatesYA);

	int cSizeZ = abs(start_a[2] - end_a[2]) + 1;
	if (cSizeZ > maxSizeA)
		maxSizeA = cSizeZ;
	vector<int> coordinatesZA(cSizeZ, 0);
	generateCoordinates(start_a[2], end_a[2], coordinatesZA);

	// store all posible combinations of coordinates
	std::vector<Point*> pointsA;
	int cnt = (cSizeX > 0 ? cSizeX : 1) * (cSizeY > 0 ? cSizeY : 1) * (cSizeZ > 0 ? cSizeZ : 1); // TODO - preveri tole, ker pri velikih cifrah pride do "out of memory exception" (program porabi > 2GB RAM)
	for (int i = 0; i < cnt; i++)
		pointsA.push_back(new Point());

    cout<<"-----------COORDINATES A ----------"<<endl;
	int i = 0;
	for (int x = 0; x < cSizeX; x++)
	{
		for (int y = 0; y < cSizeY; y++)
		{
			for (int z = 0; z < cSizeZ; z++)
			{
				pointsA[i]->setX(coordinatesXA[x]);
				pointsA[i]->setY(coordinatesYA[y]);
				pointsA[i++]->setZ(coordinatesZA[z]);
                //cout<<"("<<pointsA[i-1]->getX()<<" "<<pointsA[i-1]->getY()<<" "<<pointsA[i-1]->getZ()<<")"<<endl;
			}
		}
	}


	// generate all coordinates for B
	int maxSizeB = INT_MIN;
	cSizeX = abs(start_b[0] - end_b[0]) + 1;
	if (cSizeX > maxSizeB)
		maxSizeB = cSizeX;
	vector<int> coordinatesXB(cSizeX, 0);
	generateCoordinates(start_b[0], end_b[0], coordinatesXB);

	cSizeY = abs(start_b[1] - end_b[1]) + 1;
	if (cSizeY > maxSizeB)
		maxSizeB = cSizeY;
	vector<int> coordinatesYB(cSizeY, 0);
	generateCoordinates(start_b[1], end_b[1], coordinatesYB);

	cSizeZ = abs(start_b[2] - end_b[2]) + 1;
	if (cSizeZ > maxSizeB)
		maxSizeB = cSizeZ;
	vector<int> coordinatesZB(cSizeZ, 0);
	generateCoordinates(start_b[2], end_b[2], coordinatesZB);

	// store all posible combinations of coordinates
	std::vector<Point*> pointsB;
	cnt = (cSizeX > 0 ? cSizeX : 1) * (cSizeY > 0 ? cSizeY : 1) * (cSizeZ > 0 ? cSizeZ : 1); // TODO - preveri tole, ker pri velikih cifrah pride do "out of memory exception" (program porabi > 2GB RAM)
	for (int i = 0; i < cnt; i++)
		pointsB.push_back(new Point());

	i = 0;
    cout<<"-----------COORDINATES B ----------"<<endl;

	for (int x = 0; x < cSizeX; x++)
	{
		for (int y = 0; y < cSizeY; y++)
		{
			for (int z = 0; z < cSizeZ; z++)
			{
				pointsB[i]->setX(coordinatesXB[x]);
				pointsB[i]->setY(coordinatesYB[y]);
				pointsB[i++]->setZ(coordinatesZB[z]);
                //cout<<"("<<pointsB[i-1]->getX()<<" "<<pointsB[i-1]->getY()<<" "<<pointsB[i-1]->getZ()<<")"<<endl;
			}
		}
	}

	Drone droneA(Point(start_a), Point(end_a), pointsA);
	Drone droneB(Point(start_b), Point(end_b), pointsB);

	/*cout << "All A coordinates:" << endl;
	for (size_t i = 0; i < pointsA.size(); i++)
		cout << pointsA.at(i)->toString() << endl;

	cout << endl << "All B coordinates:" << endl;

	for (size_t i = 0; i < pointsB.size(); i++)
		cout << pointsB.at(i)->toString() << endl;*/

	dronesPath(droneA, droneB);

	for (const auto p : pointsA)
		delete p;
	for (const auto p : pointsB)
		delete p;

	// TODO - check if I cleaned everything


    // delete droneB;
	return 0;
}
