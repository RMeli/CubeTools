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
#include <vector>
#include <array>
#include <iomanip>

#include "Cube.h"

using namespace std;

int main(int argc,char *argv[])
{
    cerr << "\n##########" << endl;
    cerr << "CUBE_SHIFT" << endl;
    cerr << "##########\n" << endl;

    // Check the number of command line arguments
    if( argc != 5)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide the shift in every direction." << endl;

        exit(-1);
    }

    // Load Cube file
    string s(argv[1]);
    cerr << "Loading... " << s;
    Cube c(s);
    cerr << " ...Loaded!" << endl;

    // Read shifts
    double aa( stof(argv[2]) );
    double bb( stof(argv[3]) );
    double cc( stof(argv[4]) );

    // Shift atoms
    vector<array<double,5>> atoms( c.shift_atoms(aa,bb,cc) );

    // Print header (no atoms)
    c.print_header(cout);

    unsigned int Natoms( atoms.size() );

    // Print shifted atoms
    for(unsigned int i(0); i < Natoms; i++)
    {
        cout << fixed << std::setprecision(0) << std::setw(5)<< atoms[i][0];

        for(unsigned int j(1); j < 5; j++)
        {
            cout << fixed << std::setprecision(6) << std::setw(12) << atoms[i][j];
        }

        cout << endl;
    }

    cerr << "\nCUBE_SHIFT ended succesfully!\n" << endl;

    return 0;
}
