#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>
#include "Drone.h"
#include "Point.h"

using namespace std;

int _x = 0, _y = 0, _z = 0;
Point* curentA;
Point* curentB;

int GetValue(int start, int end) {
	if (start < end) start = start + 1;
	else start = start - 1;

	int value = start;
	// yield value
	return value;
}

Point GetVertex(Point start, Point end, Point current) {
	for (int x = current.getX(); x < GetValue(start.getX(), end.getX()); x++) {
		for (int y = current.getY(); y < GetValue(start.getY(), end.getY()); y++) {
			for (int z = current.getZ(); z < GetValue(start.getZ(), end.getZ()); z++) {
				// yield CreateVertex();
				current.setX(x);
				current.setY(y);
				current.setZ(z);
				return Point(x, y, z);
			}
		}
	}

	return Point();
}

bool Feasible(Point a, Point b) {
	// vsaj ena izmed koordinat mora biti različna
	if (a.getX() != b.getX())
		return true;
	if (a.getY() != b.getY())
		return true;
	if (a.getZ() != b.getZ())
		return true;
	return false;
}

bool Valid(Point a, Point b) {
	int lenX = abs(a.getX() - b.getX());
	int lenY = abs(a.getY() - b.getY());
	int lenZ = abs(a.getZ() - b.getZ());

	return lenX <= 1 && lenY <= 1 && lenZ <= 1 && (lenX + lenY + lenZ <= 1);
}

bool pointsOK(Point a, Point b, Point prevA, Point prevB) {
	return (abs(prevA.getX() - a.getX()) <= 1 && abs(prevA.getY() - a.getY()) <= 1 && abs(prevA.getZ() - a.getZ()) <= 1 && abs(prevB.getX() - b.getX()) <= 1 && abs(prevB.getY() - b.getY()) <= 1 && abs(prevB.getZ() - b.getZ()) <= 1);
}

void D22(Drone& A, Drone& B) {
	int max_a_X = abs(A.getStartPosition().getX() - A.getEndPosition().getX());
	int max_a_Y = abs(A.getStartPosition().getY() - A.getEndPosition().getY());
	int max_a_Z = abs(A.getStartPosition().getZ() - A.getEndPosition().getZ());
	int max_b_X = abs(B.getStartPosition().getX() - B.getEndPosition().getX());
	int max_b_Y = abs(B.getStartPosition().getY() - B.getEndPosition().getY());
	int max_b_Z = abs(B.getStartPosition().getZ() - B.getEndPosition().getZ());

	int a_toward_X = (A.getStartPosition().getX() <= A.getEndPosition().getX() ? 1 : -1);
	int a_toward_Y = (A.getStartPosition().getY() <= A.getEndPosition().getY() ? 1 : -1);
	int a_toward_Z = (A.getStartPosition().getZ() <= A.getEndPosition().getZ() ? 1 : -1);
	int b_toward_X = (B.getStartPosition().getX() <= B.getEndPosition().getX() ? 1 : -1);
	int b_toward_Y = (B.getStartPosition().getY() <= B.getEndPosition().getY() ? 1 : -1);
	int b_toward_Z = (B.getStartPosition().getZ() <= B.getEndPosition().getZ() ? 1 : -1);

	int x_to = 0, y_to = 0, z_to = 0;
	A.addToPath(A.getStartPosition());
	for (int x = 0; x <= max_a_X; x++)
	{
		for (int y = 0; y <= max_a_Y; y++)
		{
			for (int z = 0; z <= max_a_Z; z++)
			{
				Point new_coord(A.getStartPosition().getX() + x * a_toward_X, A.getStartPosition().getY() + y * a_toward_Y, A.getStartPosition().getZ() + z * a_toward_Z);
				if (Valid(A.getCoordinate(A.getPathSize() - 1), new_coord))
				{
					A.addToPath(new_coord);
				}
			}
		}
	}

	x_to = 0, y_to = 0, z_to = 0;
	B.addToPath(B.getStartPosition());
	for (int x = 0; x <= max_b_X; x++)
	{
		for (int y = 0; y <= max_b_Y; y++)
		{
			for (int z = 0; z <= max_b_Z; z++)
			{
				Point new_coord(B.getStartPosition().getX() + x * b_toward_X, B.getStartPosition().getY() + y * b_toward_Y, B.getStartPosition().getZ() + z * b_toward_Z);
				if (Valid(B.getCoordinate(B.getPathSize() - 1), new_coord))
				{
					B.addToPath(new_coord);
				}
			}
		}
	}

	// izenačimo dolžino poti
	while(A.getPathSize() < B.getPathSize()){
		A.addToPath(A.getEndPosition());
	}

	while(B.getPathSize() < A.getPathSize()){
		B.addToPath(B.getEndPosition());
	}


	// preverimo če kje trčita
	for (size_t i = 0; i < A.getPathSize()-2; i++)
	{
		// če je prišlo do trka, bo B šel okoli te točke
		if (A.getCoordinate(i + 1) == B.getCoordinate(i + 1))
		{
			cout<<"Trk"<<endl;
			// shranimo točko pred točko in točko trka
			Point begin = B.getCoordinate(i);
			Point collision = B.getCoordinate(i + 1);
			Point end = B.getCoordinate(i + 2);

			if (collision == Point() || end == Point())
				break;

			Point between_1(0, 0, 0);
			Point between_2(0, 0, 0);
			B.removeCoordinateAt(i + 1);
			// izračunamo razlike
			int beginX = collision.getX() - begin.getX();
			int beginY = collision.getY() - begin.getY();
			int beginZ = collision.getZ() - begin.getZ();

			// int endX = end.getX() - collision.getX();
			// int endY = end.getY() - collision.getY();
			// int endZ = end.getZ() - collision.getZ();

			int moveX = 0;
			int moveY = 0;
			// int moveZ = 0;

			if (abs(beginX) > 0)
			{
				// premaknemo po y, da se izognemo trku po x
				between_1.setX(begin.getX());
				between_1.setY(begin.getY() + 1);
				between_1.setZ(begin.getZ());

				// ustrezno premaknemo vzporedno do naslednje tocke
				between_2.setX(collision.getX());
				between_2.setY(collision.getY() + 1);
				between_2.setZ(collision.getZ());

				moveY = 1;
			}
			if (abs(beginY) > 0)
			{
				// premaknemo po x
				between_1.setX(begin.getX() + 1);
				between_1.setY(begin.getY());
				between_1.setZ(begin.getZ());

				// ustrezno premaknemo vzporedno do naslednje tocke
				between_2.setX(collision.getX() + 1);
				between_2.setY(collision.getY());
				between_2.setZ(collision.getZ());

				moveX = 1;
			}
			if (abs(beginZ) > 0)
			{
				// premaknemo po x
				between_1.setX(begin.getX() + 1);
				between_1.setY(begin.getY());
				between_1.setZ(begin.getZ());

				// ustrezno premaknemo vzporedno do naslednje tocke
				between_2.setX(collision.getX() + 1);
				between_2.setY(collision.getY());
				between_2.setZ(collision.getZ());

				moveX = 1;
			}

			// dodamo v pot
			A.addToPathAtIndex(i + 1, A.getCoordinate(i + 1));
			A.addToPathAtIndex(i + 1, A.getCoordinate(i + 1));

			B.addToPathAtIndex(i + 1, between_1);
			B.addToPathAtIndex(i + 2, between_2);

			between_1.setX(end.getX() + moveX);
			between_1.setY(end.getY() + moveY);
			between_1.setZ(end.getZ());

			// dodamo v pot
			A.addToPathAtIndex(i + 2, A.getCoordinate(i + 1));
			B.addToPathAtIndex(i + 3, between_1);
		}

		// preverimo, če je prišlo do izmenjave pozicij
		if (i > 0 && A.getCoordinate(i - 1) == B.getCoordinate(i) && A.getCoordinate(i) == B.getCoordinate(i - 1))
		{
			// trenutno je tole hard-coded za primer (6-parallel.in)
			// TODO - testiraj še na kakšnem primeru
			cout << "izmenjava" << endl;
			Point aPrev = A.getCoordinate(i - 1);
			Point bPrev = B.getCoordinate(i - 1);

			aPrev.setY(aPrev.getY() - 1);

			A.addToPathAtIndex(i, aPrev);
			B.addToPathAtIndex(i++, bPrev);

			aPrev.setX(aPrev.getX() - 1);
			B.setIndex(B.getIndex() - 1);
			bPrev = B.getNext();

			A.addToPathAtIndex(i, aPrev);
			B.addToPathAtIndex(i++, bPrev);
		}
	}



	std::cout << endl << "Rezultat" << endl;
	cout << "------------------------" << endl;
	int ia = 0, ib = 0;
	for (int i = 0; i < (int)max(A.getPathSize(), B.getPathSize()); i++) {
		cout << A.getCoordinate(ia).toString() << " " << B.getCoordinate(ib).toString() << "\n";

		if (ia + 1 < A.getPathSize()) ia++;
		if (ib + 1 < B.getPathSize()) ib++;
	}


	// izpis za prikaz v Blenderju
	// cout << "A:" << endl;
	// for (size_t i = 0; i < A.getPathSize(); i++) {
	// 	cout << A.getCoordinate(i).toString() << ", ";
	// }

	// cout << "\nB:" << endl;
	// for (size_t i = 0; i < B.getPathSize(); i++) {
	// 	cout << B.getCoordinate(i).toString() << ", ";
	// }
}


void writeToFile(Drone A, Drone B) {
	ofstream outFile("result.out");

	int ia = 0, ib = 0;
	for (int i = 0; i < (int)max(A.getPathSize(), B.getPathSize()); i++) {
		outFile << A.getCoordinate(ia).toString() << " " << B.getCoordinate(ib).toString() << endl;

		if (ia + 1 < A.getPathSize()) ia++;
		if (ib + 1 < B.getPathSize()) ib++;
	}

	outFile.close();
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		cout << "Uporaba: ./main [datoteka]" << endl;
		exit(1);
	}

	ifstream file(argv[1], ios::in);
	if (!file.is_open()) {
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

	cout << "Working with: " << argv[1] << endl;

	Drone droneA = Drone(Point(start_a), Point(end_a));
	Drone droneB = Drone(Point(start_b), Point(end_b));

	cout << droneA.toString() << endl;
	cout << droneB.toString() << endl;


	D22(droneA, droneB);

	// writeToFile(droneA, droneB);

	return 0;
}
