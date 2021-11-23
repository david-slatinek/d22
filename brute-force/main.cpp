#include <iostream>
#include <fstream>

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

    const int cSize = abs(start_a[0] - end_a[0]) + 1;
    int coordinates[cSize];

    generateCoordinates(start_a[0], end_a[0], coordinates);

    for (const int &x : coordinates)
        cout << x << " ";

    cout << endl;

    return 0;
}