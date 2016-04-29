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

#include "function.h"

#include <cmath>

double gaussian_1d(double r,double mu,double sigma)
{
    double norm( 1. / (std::sqrt(2.*M_PI) * sigma) );

    return norm * std::exp( -std::pow(r-mu,2) / (2.*std::pow(sigma,2)));
}

double gaussian_3d(std::array<double,3> r,std::array<double,3> mu,std::array<double,3> sigma)
{
    double g(1);

    for(unsigned int i(0); i < 3; i++)
    {
        g *= gaussian_1d(r[i],mu[i],sigma[i]);
    }

    return g;
}
