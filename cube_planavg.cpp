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
#include <string>
#include <iomanip>

#include "Cube.h"
#include "average.h"

using namespace std;

int main(int argc,char *argv[])
{
    cerr << "\n#########" << endl;
    cerr << "CUBE_PLANAVG" << endl;
    cerr << "#########\n" << endl;

    // Check the number of commandi line arguments
    if( argc < 3)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide at least two cube files." << endl;

        exit(-1);
    }

    // Load cube file
    string s(argv[1]);
    cerr << "Loading... " << s;
    Cube c(s);
    cerr << " ...Loaded!\n" << endl;

    // Read IDIR from input file
    unsigned int idir( atoi(argv[2]) );

    // Compute planar average along IDIR
    std::vector<std::array<double,2>> pa( planar_average(c,idir) );

    // Print comments at the beginning of the output file
    cout << "# Coordinate along IDIR " + to_string(idir) + " ()";
    cout << " | Cube planar average along IDIR " + to_string(idir) + " ()" << endl;
    cout << "# BEWARE: The units are the one of the Cube file." << endl;

    // Number of data points
    unsigned int N( pa.size() );

    for(unsigned int idx(0); idx < N; idx++)
    {
        cout << showpos << fixed << scientific << setprecision(6) << setw(15);
        cout << pa[idx][0] << ' ' << pa[idx][1] << endl;
    }

    cerr << "\nCUBE_PLANAVG ended succesfully!\n" << endl;

    return 0;
}
