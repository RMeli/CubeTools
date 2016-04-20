#include <iostream>
#include <cstdlib>

#include "Cube.h"

using namespace std;

int main(int argc,char *argv[])
{
    cerr << "\n#########" << endl;
    cerr << "CUBE_SUB" << endl;
    cerr << "#########\n" << endl;

    // Check the number of commandi line arguments
    if( argc < 3)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide at least two cube files." << endl;

        exit(-1);
    }

    // Load first cube file
    string s(argv[1]);
    cerr << "Loading... " << s;
    Cube out(s);
    cerr << " ...Loaded!" << endl;

    // Load second cube file
    s = argv[2];
    cerr << "Loading... " << s;
    Cube tmp(s);
    cerr << " ...Loaded!" << endl;

    for(int i(2); i < argc; i++)
    {
        out = out - tmp;

        if( (i+1) != argc )
        {
            // Load successive cube file
            s = argv[i+1];
            cerr << "Loading... " << s;
            tmp = Cube(s);
            cerr << " ...Loaded!" << endl;
        }


    }

    out.print(cout);

    cerr << "\nCUBE_ADD ended succesfully!\n" << endl;

    return 0;
}
