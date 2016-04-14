#include <iostream>

#include "Cube.h"

using namespace std;

int main()
{
    //cout << "Loading cube file..." << endl;

    Cube c("test1.cube");

    //cout << "Cube file loaded!" << endl;

    //cout << "\nCube file header:" << endl;
    //c.print_header(cout);

    //cout << "\nCube file data:" << endl;
    //c.print_data(cout,5);
    //cout << "..." << endl;
    //c.print_data(cout,-5);

    Cube cc("test2.cube");

    if( c.compare_headers(cc) )
    {
        cout << "CUBE FILES HAVE EQUAL HEADERS" << endl;
    }
    else
    {
        cout << "CUBE FILES HAVE DIFFERENT HEADERS" << endl;
    }

    return 0;
}
