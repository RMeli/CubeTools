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

#include "Cube.h"
#include "average.h"

using namespace std;

int main(int argc,char *argv[])
{
    cerr << "\n##########" << endl;
    cerr << "CUBE_LOCAL" << endl;
    cerr << "##########\n" << endl;

    // Check the number of command line arguments
    if( argc < 4)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide a cube file." << endl;
        cerr << "       You should provide a sigma." << endl;
        cerr << "       You should provide an atomic number." << endl;

        exit(-1);
    }

    // Load cube file
    string s(argv[1]);
    cerr << "Loading... " << s;
    Cube c(s);
    cerr << " ...Loaded!" << endl;

    // Store Gaussian's std
    double sigma( stod(argv[2]) );

    // Store atomic number
    double Z( stoi(argv[3]) );

    cerr << "\nComputing Gaussian weighted average." << endl;
    cerr << "   Sigma: " << sigma << endl;
    cerr << "    Zeta: " << Z << endl << endl;

    // Extract atoms
    std::vector<std::array<double,5>> atoms( c.get_atoms() );

    // Total number of atoms
    unsigned int n( atoms.size() );

    // Current atomic position
    array<double,3> r{{0,0,0}};

    // Local potential
    double loc(0);

    cout << "# Gaussian weigted average" << endl;
    cout << "# Sigma: " <<  sigma << endl;
    cout << "# Zeta: " <<  Z << endl;
    cout << "# Atomic coordinates and local averaged quantity" << endl;

    for(unsigned int i(0); i < n; i++)
    {
        if( Z == (unsigned int)atoms[i][0] )
        {
            r[0] = atoms[i][2];
            r[1] = atoms[i][3];
            r[2] = atoms[i][4];

            loc = g_average(c,r,{{sigma,sigma,sigma}});

            cout << fixed << scientific << setprecision(5) << setw(13) << r[0];
            cout << fixed << scientific << setprecision(5) << setw(13) << r[1];
            cout << fixed << scientific << setprecision(5) << setw(13) << r[2];
            cout << fixed << scientific << setprecision(5) << setw(13) << loc * 13.605698066 << endl;
        }
    }

    cerr << "\nCUBE_LOCAL ended successfully!\n" << endl;

    return 0;
}
