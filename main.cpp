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
#include "interpolation.h"

using namespace std;

int main()
{
    Cube c("out.cube");

    //std::array<double, 3> R{{11.936994,8.860931,3.615049}};
    //std::array<double,3> sigma{{1,0.001,1}};

    //cout << "G-average:" << g_average(c,R,sigma, true) << endl;

    //FOURIER INTERPOLATION

    std::vector<std::array<double,2>> pa(planar_average(c,3));

    cerr << pa.size() << std::endl;

    for(unsigned int idx(0); idx < pa.size(); idx++)
    {
        cout << std::fixed << std::scientific << std::setprecision(5) << std::setw(13);
        cout << pa[idx][0] << ' ' << pa[idx][1] << endl;
    }


    cout << "\n\n# Fourier Interpolation" << endl;

    std::vector<std::array<double,2>> fpa(fourier_interpolation(pa,400));
    cerr << fpa.size() << endl;
    for(unsigned int idx(0); idx < fpa.size(); idx++)
    {
        cout << std::fixed << std::scientific << std::setprecision(5) << std::setw(13);
        cout << fpa[idx][0] << ' ' << fpa[idx][1] << endl;
    }

    return 0;
}
