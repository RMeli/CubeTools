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
#include "interpolation.h"
#include "typedef.h"

using namespace std;

int main(int argc,char *argv[])
{
    cerr << "\n###########" << endl;
    cerr << "CUBE_MACROAVG" << endl;
    cerr << "###########\n" << endl;

    // Check the number of commandi line arguments
    if( argc != 4 and argc != 5)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide a cube file and a direction and sigma." << endl;
        cerr << "       Optionally you can provide the number of data points." << endl;
        cerr << "       Additional data points are obtained by Foruier interpolation." << endl;

        exit(-1);
    }

    // Load cube file
    string s(argv[1]);
    cerr << "Loading... " << s;
    Cube c(s);
    cerr << " ...Loaded!\n" << endl;

    // Read IDIR from input file
    uint idir( atoi(argv[2]) );

    // Sigma (macroscopic window width)
    double sigma( atof(argv[3]) );

    int npoints(-1);

    if(argc == 5)
    {
        npoints = atoi(argv[4]);
    }

    // Compute macroscopic average along IDIR
    Table ma( macro_average(c,idir,npoints,sigma) );

    // Print comments at the beginning of the output file
    cout << "# Coordinate along IDIR " + to_string(idir) + " ()";
    cout << " | Cube macroscopic average along IDIR " + to_string(idir) + " ()" << endl;
    cout << "# BEWARE: The units are the one of the Cube file." << endl;

    // Number of data points
    unsigned int N( ma.size() );

    for(unsigned int idx(0); idx < N; idx++)
    {
        cout << showpos << fixed << scientific << setprecision(6) << setw(15);
        cout << ma[idx][0] << ' ' << ma[idx][1] << endl;
    }

    cerr << "\nCUBE_MACROAVG ended succesfully!\n" << endl;

    return 0;
}
