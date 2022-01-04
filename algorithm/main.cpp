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
	return sqrt(pow(b.getX() - a.getX(), 2) + pow(b.getY() - a.getY(), 2) + pow(b.getZ() - a.getZ(), 2)) == 1;
}

bool pointsOK(Point a, Point b, Point prevA, Point prevB) {
	return (abs(prevA.getX() - a.getX()) <= 1 && abs(prevA.getY() - a.getY()) <= 1 && abs(prevA.getZ() - a.getZ()) <= 1 && abs(prevB.getX() - b.getX()) <= 1 && abs(prevB.getY() - b.getY()) <= 1 && abs(prevB.getZ() - b.getZ()) <= 1);
}

void D22(Drone& A, Drone& B) {
	/*for (int x = A.getStartPosition().getX(); abs(x) <= abs(x) + abs(x - A.getEndPosition().getX()); x++)
	{
		for (int y = A.getStartPosition().getY(); abs(y) <= abs(y) + abs(y - A.getEndPosition().getY()); y++)
		{
			for (int z = A.getStartPosition().getZ(); abs(z) <= abs(z) + abs(z - A.getEndPosition().getZ()); z++)
			{
				A.addToPath(Point(x, y, z));
			}
		}
	}

	for (int x = B.getStartPosition().getX(); abs(x) <= abs(x) + abs(x - B.getEndPosition().getX()); x++)
	{
		for (int y = B.getStartPosition().getY(); abs(y) <= abs(y) + abs(y - B.getEndPosition().getY()); y++)
		{
			for (int z = B.getStartPosition().getZ(); abs(z) <= abs(z) + abs(z - B.getEndPosition().getZ()); z++)
			{
				B.addToPath(Point(x, y, z));
			}
		}
	}*/

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

	A.addToPath(A.getStartPosition());
	for (int x = 1; x <= max_a_X; x++)
	{
		for (int y = 1; y <= max_a_Y; y++)
		{
			for (int z = 1; z <= max_a_Z; z++)
			{
				Point new_coord(A.getStartPosition().getX() + x * a_toward_X, A.getStartPosition().getY() + y * a_toward_Y, A.getStartPosition().getZ() + z * a_toward_Z);
				if (Valid(A.getCoordinate(A.getPathSize() - 1), new_coord))
				{
					A.addToPath(new_coord);
				}
			}
		}
	}

	B.addToPath(B.getStartPosition());
	for (int x = 1; x <= max_b_X; x++)
	{
		for (int y = 1; y <= max_b_Y; y++)
		{
			for (int z = 1; z <= max_b_Z; z++)
			{
				B.addToPath(Point(B.getStartPosition().getX() + x * b_toward_X, B.getStartPosition().getY() + y * b_toward_Y, B.getStartPosition().getZ() + z * b_toward_Z));
			}
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
	/*cout << "A:" << endl;
	for (size_t i = 0; i < (int)min(A.getPathSize(), B.getPathSize()); i++) {
		cout << A.getCoordinate(i).toString() << ", ";
	}

	cout << "\nB:" << endl;
	for (size_t i = 0; i < (int)min(A.getPathSize(), B.getPathSize()); i++) {
		cout << B.getCoordinate(i).toString() << ", ";
	}*/
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
