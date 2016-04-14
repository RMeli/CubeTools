#include <iostream>
#include <cstdlib>

#include "Cube.h"

using namespace std;

int main(int argc,char *argv[])
{
    // Check the number of commandi line arguments
    if( argc < 3)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide at least two cube files." << endl;

        exit(-1);
    }

    // Load first cube file
    string s(argv[1]);
    Cube tmp(s);

    // Declare output cube file
    Cube out;

    // Copy the header of tmp
    out.copy_header(tmp); // Also resize data and fill it with zeros

    for(int i(1); i < argc; i++)
    {
        out = out + tmp;

        if( (i+1) != argc )
        {
            // Load successive cube file
            s = argv[i];
            tmp = Cube(s);
        }
    }

    out.print(cout);

    return 0;
}