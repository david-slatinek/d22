#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>
#include "Drone.h"
#include "Point.h"

using namespace std;

int _x = 0, _y = 0, _z = 0;

int GetValue(int start, int end) {
	int value = start;
	if (start < end) start = start + 1;
	else start = start - 1;

	// yield value
	return value;
}

Point GetVertex(Point start, Point end) {
	for (int x = _x; x < GetValue(start.getX(), end.getX()); x++) {
		for (int y = _y; y < GetValue(start.getY(), end.getY()); y++) {
			for (int z = _z; z < GetValue(start.getZ(), end.getZ()); z++) {
				// yield CreateVertex();
				_x = x;
				_y = y;
				_z = z;
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
	A.addToPath(GetVertex(A.getStartPosition(), A.getEndPosition()));
	B.addToPath(GetVertex(B.getStartPosition(), B.getEndPosition()));

	// accept starting points
	A.addToPath(A.getStartPosition());
	B.addToPath(B.getStartPosition());

	Point a, b;
	bool restA, restB;
	while (!A.IsAtEnd() && !B.IsAtEnd()) {
		a = GetVertex(A.getStartPosition(), A.getEndPosition());
		b = GetVertex(B.getStartPosition(), B.getEndPosition());

		// TODO

		if(!A.isEnd()){
			a = GetVertex(A.getStartPosition(), A.getEndPosition());
		}
		if(!B.isEnd()){
			b = GetVertex(B.getStartPosition(), B.getEndPosition());
		}

		if(restA && !restB){
			if(Valid(b, B.getCurrentPosition()) && Feasible(a, b)){
				B.addToPath(b);
			}
			else{
				B.backtrack(b);
			}
		}
		else if(!restA && restB){
			if(Valid(a, A.getCurrentPosition()) && Feasible(a, b)){
				A.addToPath(a);
			}
			else{
				A.backtrack(a);
			}
		}
		else{
			if(Feasible(a, b)){
				if(Valid(b, B.getCurrentPosition())){
					B.addToPath(b);

				}
				else{
					B.backtrack(b);
				}

			}
			else{
				if(Valid(a, A.getCurrentPosition()))
				{
					A.addToPath(a);
				}
				else{
					A.backtrack(a);
				}

				if(Valid(b, B.getCurrentPosition())){
					B.addToPath(b);
				}
				else{
					B.backtrack(b);
				}
			}
		}
	}


	std::cout << endl << "Rezultat" << endl;
	cout << "------------------------" << endl;
	int ia = 0, ib = 0;
	for (int i = 0; i < (int)min(A.getPathSize(), B.getPathSize()); i++) {
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
	for (int i = 0; i < (int)min(A.getPathSize(), B.getPathSize()); i++) {
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
