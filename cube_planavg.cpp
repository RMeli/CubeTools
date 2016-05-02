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

using namespace std;

int main(int argc,char *argv[])
{
    cerr << "\n###########" << endl;
    cerr << "CUBE_PLANAVG" << endl;
    cerr << "###########\n" << endl;

    // Check the number of commandi line arguments
    if( argc != 3 and argc != 4)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide a cube file and a direction." << endl;
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
    unsigned int idir( atoi(argv[2]) );

    unsigned int npoints(0);

    if(argc == 4)
    {
        npoints = atoi(argv[3]);
    }

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

    if(argc == 4)
    {
        // Perform Fourier interpolation
        std::vector<std::array<double,2>> fpa(fourier_interpolation(pa,npoints));

        // Print comments at the beginning of the Fourier data set
        cout << "\n\n# Coordinate along IDIR " + to_string(idir) + " ()";
        cout << " | Fourier interpolated planar average along IDIR " + to_string(idir) + " ()" << endl;
        cout << "# BEWARE: The units are the one of the Cube file." << endl;

        for(unsigned int idx(0); idx < npoints; idx++)
        {
            cout << showpos << fixed << scientific << setprecision(6) << setw(15);
            cout << fpa[idx][0] << ' ' << fpa[idx][1] << endl;
        }
    }

    cerr << "\nCUBE_PLANAVG ended succesfully!\n" << endl;

    return 0;
}
