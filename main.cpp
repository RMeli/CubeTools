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
#include <iomanip>

#include "Cube.h"
#include "average.h"

using namespace std;

int main()
{
    Cube c("out.cube");

    Matrix data(c.reshape());

    unsigned int Na(data.size());
    unsigned int Nb(data[0].size());
    unsigned int Nc(data[0][0].size());

    std::vector<std::array<double,2>> pa(planar_average(c,3));

    for(unsigned int idx(0); idx < Nc; idx++)
    {
        cout << std::fixed << std::scientific << std::setprecision(5) << std::setw(13);
        cout << pa[idx][0] << ' ' << pa[idx][1] << endl;
    }

    return 0;
}
