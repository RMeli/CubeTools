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
    cerr << "\n###########" << endl;
    cerr << "CUBE_TOTAVG" << endl;
    cerr << "###########\n" << endl;

    // Check the number of commandi line arguments
    if( argc != 2)
    {
        cerr << "ERROR: Invalid number of arguments." << endl;
        cerr << "       You should provide one cube files." << endl;

        exit(-1);
    }

    // Load cube file
    string s(argv[1]);
    cerr << "Loading... " << s;
    Cube c(s);
    cerr << " ...Loaded!\n" << endl;

    cerr << "----------------------------" << endl;
    cerr << showpos << fixed << scientific << setprecision(6) << setw(19);
    cerr << "\nTotal average: " << total_average(c) << endl;
    cerr << "\n----------------------------" << endl;

    cerr << "\nCUBE_TOTAVG ended succesfully!\n" << endl;

    return 0;
}
