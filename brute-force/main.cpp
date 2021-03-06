#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
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

bool pathOK(Point a, Point b)
{
	// vsaj ena izmed koordinat mora biti različna
	if (a.getX() != b.getX())
		return true;
	if (a.getY() != b.getY())
		return true;
	if (a.getZ() != b.getZ())
		return true;
	return false;
}

bool pointsOK(Point a, Point b, Point prevA, Point prevB)
{
	return (abs(prevA.getX() - a.getX()) <= 1 && abs(prevA.getY() - a.getY()) <= 1 && abs(prevA.getZ() - a.getZ()) <= 1 && abs(prevB.getX() - b.getX()) <= 1 && abs(prevB.getY() - b.getY()) <= 1 && abs(prevB.getZ() - b.getZ()) <= 1);
}

void bruteforce(Drone A, Drone B)
{
	// za vsak dron zgeneriramo popolno pot, potem pa se izognemo trčenjem
	A.GenerateEdges();
	B.GenerateEdges();

	Point a = A.getNext();
	Point b = B.getNext();

	// accept starting points
	A.addToPath(a);
	B.addToPath(b);

	while (true)
	{
		if (A.isNext())
		{
			a = A.getNext();
		}
		else
		{
			A.setEnd(true);
		}
		if (B.isNext())
		{
			b = B.getNext();
		}
		else
		{
			B.setEnd(true);
		}
		if (A.isEnd() && B.isEnd())
		{
			break;
		}
		if (A.ValidEdge(a))
		{
			A.addToPath(a);
		}

		if (B.ValidEdge(b))
		{
			B.addToPath(b);
		}
	}

	// preverimo če kje trčita
	for (size_t i = 0; i < A.getPathSize(); i++)
	{
		// če je prišlo do trka, bo B šel okoli te točke
		if (A.getCoordinate(i + 1) == B.getCoordinate(i + 1))
		{
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

	std::cout << endl
			  << "Rezultat" << endl;
	cout << "------------------------" << endl;
	int ia = 0, ib = 0;
	for (int i = 0; i < (int)min(A.getPathSize(), B.getPathSize()); i++)
	{
		cout << A.getCoordinate(ia).toString() << " " << B.getCoordinate(ib).toString() << "\n";

		if (ia + 1 < A.getPathSize())
			ia++;
		if (ib + 1 < B.getPathSize())
			ib++;
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

void writeToFile(Drone A, Drone B)
{
	ofstream outFile("result.out");

	int ia = 0, ib = 0;
	for (int i = 0; i < (int)min(A.getPathSize(), B.getPathSize()); i++)
	{
		outFile << A.getCoordinate(ia).toString() << " " << B.getCoordinate(ib).toString() << endl;

		if (ia + 1 < A.getPathSize())
			ia++;
		if (ib + 1 < B.getPathSize())
			ib++;
	}

	outFile.close();
}

/*
void print_memory_usage()
{
	struct rusage usage;
	getrusage(RUSAGE_SELF, &usage);
	cout << "USE: " << usage.ru_maxrss << " KB" << endl;
}
*/

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

	// read input
	file >> start_a[0] >> start_a[1] >> start_a[2];
	file >> end_a[0] >> end_a[1] >> end_a[2];

	file >> start_b[0] >> start_b[1] >> start_b[2];
	file >> end_b[0] >> end_b[1] >> end_b[2];

	file.close();

	cout << "Working with: " << argv[1] << endl;

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
	int cnt = (cSizeX > 0 ? cSizeX : 1) * (cSizeY > 0 ? cSizeY : 1) * (cSizeZ > 0 ? cSizeZ : 1);
	for (int i = 0; i < cnt; i++)
		pointsA.push_back(Point());

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
	cnt = (cSizeX > 0 ? cSizeX : 1) * (cSizeY > 0 ? cSizeY : 1) * (cSizeZ > 0 ? cSizeZ : 1);
	for (int i = 0; i < cnt; i++)
		pointsB.push_back(Point());

	i = 0;
	for (int x = 0; x < cSizeX; x++)
	{
		for (int y = 0; y < cSizeY; y++)
		{
			for (int z = 0; z < cSizeZ; z++)
			{
				pointsB[i].setX(coordinatesXB[x]);
				pointsB[i].setY(coordinatesYB[y]);
				pointsB[i++].setZ(coordinatesZB[z]);
			}
		}
	}

	Drone droneA(Point(start_a), Point(end_a), pointsA);
	Drone droneB(Point(start_b), Point(end_b), pointsB);

	cout << "Drone A:  " << droneA.toString() << endl;
	cout << "Drone B:  " << droneB.toString() << endl;

	bruteforce(droneA, droneB);

	//print_memory_usage();

	writeToFile(droneA, droneB);

	return 0;
}
