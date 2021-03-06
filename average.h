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


#include "Cube.h"

#ifndef AVERAGE_H
#define AVERAGE_H

// Plane average along IDIR
Table planar_average(Cube const& c,int idir);

// Macroscopic average along IDIR
Table macro_average(Cube const& c,int idir,int m,double sigma);

// Total average
double total_average(Cube const& c);

// Gaussian weighted average (PBC activated by default)
double g_average(Cube const& c, std::array<double,3> R, std::array<double,3>sigma, bool pbc = true);

#endif
