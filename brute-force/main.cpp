#include <iostream>
#include <fstream>

using namespace std;

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

    return 0;
}