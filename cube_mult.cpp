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
    cerr << "\n##########" << endl;
    cerr << "CUBE_MULT" << endl;
    cerr << "##########\n" << endl;

    // Check the number of commandi line arguments
    if( argc != 3)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide one cube file and a number." << endl;

        exit(-1);
    }

    // Load first cube file
    string s(argv[1]);
    cerr << "Loading... " << s;
    Cube tmp(s);
    cerr << " ...Loaded!" << endl;

    // Read multiplicative constant
    unsigned int m( atoi(argv[2]) );

    // Compute multiplication
    Cube out( tmp * m );

    // Print new Cube file
    out.print(cout);

    cerr << "\nCUBE_MULT ended succesfully!\n" << endl;

    return 0;
}
