/*
 Copyright (C) 2016 Rocco Meli (rocco.meli@epfl.ch)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <iostream>
#include <cstdlib>

#include "Cube.h"

using namespace std;

int main(int argc,char *argv[])
{
    cerr << "\n#########" << endl;
    cerr << "CUBE_ADD" << endl;
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
    Cube tmp(s);
    cerr << " ...Loaded!" << endl;



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
