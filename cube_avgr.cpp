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
#include <iomanip>

#include "average.h"

using namespace std;

int main(int argc,char *argv[])
{
    cerr << "\n##########" << endl;
    cerr << "CUBE_AVGR" << endl;
    cerr << "##########\n" << endl;

    // Check the number of commandi line arguments
    if( argc != 2)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide one cube file." << endl;

        exit(-1);
    }

    // Load cube file
    string s(argv[1]);
    cerr << "Loading... " << s;
    Cube in(s);
    cerr << " ...Loaded!" << endl;

    // Compute average R
    array<double,3> R(average_r(in));

    // Printe result
    cout << endl;
    cout << "---------------------------------------" << endl << endl;
    cerr << "# Average R:" << endl;
    cerr << fixed << scientific << setprecision(5) << setw(13) << R[0];
    cerr << fixed << scientific << setprecision(5) << setw(13) << R[1];
    cerr << fixed << scientific << setprecision(5) << setw(13) << R[2] << endl;
    cout << endl << "---------------------------------------" << endl;

    cerr << "\nCUBE_AVGR ended succesfully!\n" << endl;

    return 0;
}
