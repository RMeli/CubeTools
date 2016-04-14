#include <iostream>

#include "Cube.h"

using namespace std;

int main()
{
    cout << "Loading cube file..." << endl;

    Cube c("test.cube");

    cout << "Cube file loaded!" << endl;

    cout << "\nCube file header:" << endl;
    c.print_header(cout);

    cout << "\nCube file data:" << endl;
    c.print_data(cout,5);
    cout << "..." << endl;
    c.print_data(cout,-5);
}
