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
    return (abs(prevA.getX()-a.getX())<=1 && abs(prevA.getY()-a.getY())<=1 && abs(prevA.getZ()-a.getZ())<=1 &&abs(prevB.getX()-b.getX())<=1 && abs(prevB.getY()-b.getY())<=1 && abs(prevB.getZ()-b.getZ())<=1);
}


void bruteforce(Drone A, Drone B){
    // za vsak dron zgeneriramo popolno pot, potem pa se izognemo trčenjem
    A.GenerateEdges();
    B.GenerateEdges();

    Point a = A.getNext();
    Point b = B.getNext();

    // accept starting points
    A.addToPath(a);
    B.addToPath(b);

    while(true){
        if (A.isNext()) {
			a = A.getNext();
		}
        else{
            A.setEnd(true);
        }
		if (B.isNext()) {
			b = B.getNext();
		}
        else{
            B.setEnd(true);
        }
        if(A.isEnd() && B.isEnd()){
                    break;
                }
        if(A.ValidEdge(a)){
            A.addToPath(a);
        }

        if(B.ValidEdge(b)){
            B.addToPath(b);
        }


    }



    // preverimo če kje trčita
    for (size_t i = 0; i < A.getPathSize()-2; i++)
    {
        // če je prišlo do trka, bo B šel okoli te točke
        if(A.getCoordinate(i+1) == B.getCoordinate(i+1)){
            // shranimo točko pred točko in točko trka
            Point begin = B.getCoordinate(i);
            Point collision = B.getCoordinate(i+1);
            Point end = B.getCoordinate(i+2);
            Point between_1(0, 0, 0);
            Point between_2(0, 0, 0);
            B.removeCoordinateAt(i+1);
            // izračunamo razlike
            int beginX = collision.getX() - begin.getX();
            int beginY = collision.getY() - begin.getY();
            int beginZ = collision.getZ() - begin.getZ();

            int endX = end.getX() - collision.getX();
            int endY = end.getY() - collision.getY();
            int endZ = end.getZ() - collision.getZ();

            int moveX = 0;
            int moveY = 0;
            int moveZ = 0;

            if(abs(beginX) > 0){
                // premaknemo po y, da se izognemo trku po x
                between_1.setX(begin.getX());
                between_1.setY(begin.getY()+1);
                between_1.setZ(begin.getZ());

                // ustrezno premaknemo vzporedno do naslednje tocke
                between_2.setX(collision.getX());
                between_2.setY(collision.getY()+1);
                between_2.setZ(collision.getZ());

                moveY = -1;
            }
            if(abs(beginY) > 0){
                // premaknemo po x
                between_1.setX(begin.getX()+1);
                between_1.setY(begin.getY());
                between_1.setZ(begin.getZ());

                // ustrezno premaknemo vzporedno do naslednje tocke
                between_2.setX(collision.getX()+1);
                between_2.setY(collision.getY());
                between_2.setZ(collision.getZ());

                moveX = -1;
            }
            if(abs(beginZ) > 0){
                // premaknemo po x
                between_1.setX(begin.getX()+1);
                between_1.setY(begin.getY());
                between_1.setZ(begin.getZ());

                // ustrezno premaknemo vzporedno do naslednje tocke
                between_2.setX(collision.getX()+1);
                between_2.setY(collision.getY());
                between_2.setZ(collision.getZ());

                moveX = -1;
            }

            // dodamo v pot
            A.addToPathAtIndex(i+1, A.getCoordinate(i+1));
            A.addToPathAtIndex(i+1, A.getCoordinate(i+1));

            B.addToPathAtIndex(i+1, between_1);
            B.addToPathAtIndex(i+2, between_2);

            if(abs(endX) > 0){
                // premaknemo po y, da se izognemo trku po x
                between_1.setX(end.getX());
                between_1.setY(collision.getY()+1);
                between_1.setZ(end.getZ());

                // ustrezno premaknemo vzporedno do naslednje tocke
                between_2.setX(end.getX());
                between_2.setY(end.getY());
                between_2.setZ(end.getZ());
            }
            if(abs(endY) > 0){
                // premaknemo po x
                between_1.setX(collision.getX()+1);
                between_1.setY(end.getY());
                between_1.setZ(end.getZ());

                // ustrezno premaknemo vzporedno do naslednje tocke
                between_2.setX(end.getX());
                between_2.setY(end.getY());
                between_2.setZ(end.getZ());
            }
            if(abs(endY) > 0){
                // premaknemo po x
                between_1.setX(collision.getX()+1);
                between_1.setY(end.getY());
                between_1.setZ(end.getZ());

                // ustrezno premaknemo vzporedno do naslednje tocke
                between_2.setX(end.getX());
                between_2.setY(end.getY());
                between_2.setZ(end.getZ());
            }

            // dodamo v pot
            A.addToPathAtIndex(i+2, A.getCoordinate(i+1));
            A.addToPathAtIndex(i+2, A.getCoordinate(i+1));

            B.addToPathAtIndex(i+3, between_1);
            B.addToPathAtIndex(i+4, between_2);
            i+=4;



        }

        // preverimo, če je prišlo do izmenjave pozicij
        if(i > 0 && A.getCoordinate(i-1) == B.getCoordinate(i) && A.getCoordinate(i) == B.getCoordinate(i-1)){

        }
    }

    std::cout << endl << "Rezultat" << endl;
            cout << "------------------------" << endl;
            int ia = 0, ib = 0;
            for (size_t i = 0; i < (int)min(A.getPathSize(), B.getPathSize()); i++)
            {
                cout << A.getCoordinate(ia).toString() << " " << B.getCoordinate(ib).toString() << "\n";

                if (ia + 1 < A.getPathSize()) ia++;
                if (ib + 1 < B.getPathSize()) ib++;
            }


    // std::cout << endl << "Rezultat" << endl;
	// cout << "------------------------" << endl;
	// int ia = 0, ib = 0;
	// for (size_t i = 0; i < (int)min(A.getPathSize(), B.getPathSize()); i++)
	// {
	// 	cout << A.getCoordinate(ia).toString() << " " << B.getCoordinate(ib).toString() << "\n";

	// 	if (ia + 1 < A.getPathSize()) ia++;
	// 	if (ib + 1 < B.getPathSize()) ib++;
	// }

}


// void dronesPath(Drone A, Drone B) {
// 	A.GenerateEdges();
// 	B.GenerateEdges();

// 	Point a = A.getNext();
// 	Point b = B.getNext();

// 	// accept starting points
// 	A.addToPath(a);
// 	B.addToPath(b);

// 	bool aStil = true, bStil = true;

// 	bool endA = A.IsAtEnd();
// 	bool endB = B.IsAtEnd();
// 	while (!endA || !endB) {
// 		a = A.getCurrentPosition();
// 		b = B.getCurrentPosition();
// 		aStil = true;
// 		bStil = true;

// 		if (A.isNext()) {
// 			a = A.getNext();
// 			aStil = false;
// 		}
// 		if (B.isNext()) {
// 			b = B.getNext();
// 			bStil = false;
// 		}

// 		if (aStil && !bStil) {
// 			if (B.ValidEdge() && pathOK(a, b)) {
// 				B.addToPath(b);
// 			}
// 			else {
// 				// TODO - BACKTRACK
//                 A.backtrack(a);
// 			}
// 		}
// 		else if (!aStil && bStil) {
// 			if (A.ValidEdge() && pathOK(a, b)) {
// 				A.addToPath(a);
// 			}
// 			else {
// 				// TODO - BACKTRACK
//                 B.backtrack(b);
// 			}
// 		}
// 		else {
// 			if (A.isNext()) a = A.getNext();
// 			if (B.isNext()) b = B.getNext();

// 			if (!pathOK(a, b)) {
// 				a = A.getCurrentPosition();
// 				if (B.ValidEdge()) {
// 					B.addToPath(b);
// 				}
// 				else {
//                     A.backtrack(a);
// 					// TODO - BACKTRACK
// 				}
// 			}
// 			else {
// 				if (A.ValidEdge()) {
// 					A.addToPath(a);
// 				}
// 				else {
//                     B.backtrack(b);
// 					// TODO - BACKTRACK
// 				}

// 				if (B.ValidEdge()) {
// 					B.addToPath(b);
// 				}
// 				else {
//                     A.backtrack(a);
// 					// TODO - BACKTRACK
// 				}
// 			}
// 		}

// 		endA = A.IsAtEnd();
// 		endB = B.IsAtEnd();
// 	}

// 	std::cout << endl << "Rezultat" << endl;
// 	cout << "------------------------" << endl;
// 	int ia = 0, ib = 0;
// 	for (size_t i = 0; i < (int)min(A.getPathSize(), B.getPathSize()); i++)
// 	{
// 		cout << A.getCoordinate(ia).toString() << " " << B.getCoordinate(ib).toString() << "\n";

// 		if (ia + 1 < A.getPathSize()) ia++;
// 		if (ib + 1 < B.getPathSize()) ib++;
// 	}
// }

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
	std::vector<Point> pointsA;
	int cnt = (cSizeX > 0 ? cSizeX : 1) * (cSizeY > 0 ? cSizeY : 1) * (cSizeZ > 0 ? cSizeZ : 1); // TODO - preveri tole, ker pri velikih cifrah pride do "out of memory exception" (program porabi > 2GB RAM)
	for (int i = 0; i < cnt; i++)
		pointsA.push_back(Point());

    cout<<"-----------COORDINATES A ----------"<<endl;
	int i = 0;
	for (int x = 0; x < cSizeX; x++)
	{
		for (int y = 0; y < cSizeY; y++)
		{
			for (int z = 0; z < cSizeZ; z++)
			{
				pointsA[i].setX(coordinatesXA[x]);
				pointsA[i].setY(coordinatesYA[y]);
				pointsA[i++].setZ(coordinatesZA[z]);
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
	std::vector<Point> pointsB;
	cnt = (cSizeX > 0 ? cSizeX : 1) * (cSizeY > 0 ? cSizeY : 1) * (cSizeZ > 0 ? cSizeZ : 1); // TODO - preveri tole, ker pri velikih cifrah pride do "out of memory exception" (program porabi > 2GB RAM)
	for (int i = 0; i < cnt; i++)
		pointsB.push_back(Point());

	i = 0;
    cout<<"-----------COORDINATES B ----------"<<endl;

	for (int x = 0; x < cSizeX; x++)
	{
		for (int y = 0; y < cSizeY; y++)
		{
			for (int z = 0; z < cSizeZ; z++)
			{
				pointsB[i].setX(coordinatesXB[x]);
				pointsB[i].setY(coordinatesYB[y]);
				pointsB[i++].setZ(coordinatesZB[z]);
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

	//dronesPath(droneA, droneB);
    bruteforce(droneA, droneB);
	/*for (const auto p : pointsA)
		delete p;
	for (const auto p : pointsB)
		delete p;*/

	// TODO - check if I cleaned everything


    // delete droneB;
	return 0;
}
