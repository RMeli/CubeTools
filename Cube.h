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
#include <string>
#include <array>
#include <vector>

#include "typedef.h"

#ifndef CUBE_H
#define CUBE_H

class Cube
{
public:
    // Default constructor (use copy_header to compy the header of a Cube and fill data with zeros)
    Cube();
    // Create cube file from data
    Cube(std::string fname);

    // Load Cube fro file
    void load(std::string filename);

    // Printing routines (whole cube, only header or only data)
    void print(std::ostream& out) const;
    void print_header(std::ostream& out) const;
    void print_atoms(std::ostream& out) const;
    void print_data(std::ostream& out,int lines=0) const;

    // COmpare headers
    bool header_is_compatible(const Cube& cube,double threshold=1e-12) const;
    bool header_is_equal(const Cube& cube,double threshold=1e-12) const;

    // Copy header (reinitialize data with the correct number of voxels)
    void copy_header(const Cube& cube);

    // Sum two cube files
    Cube operator+(const Cube& cube) const;
    // Subtract two cube files
    Cube operator-(const Cube& cube) const;
    // Multiply cube data by number
    Cube operator*(double) const;

    // Return reshaped DATA (rank-3 tensor instead of vector)
    Matrix reshape() const;

    // Return data
    std::vector<double> get_data() const;

    // Return Cube file origin
    std::array<double,3> get_origin() const;

    // Return axis
    std::array<double,3> get_a() const;
    std::array<double,3> get_b() const;
    std::array<double,3> get_c() const;

    // Return number of voxels
    long int get_Na() const;
    long int get_Nb() const;
    long int get_Nc() const;


    // Length of the voxel along a, b or c
    double da() const;
    double db() const;
    double dc() const;

    // Periodic boundary conditions
    double pbc(double d,unsigned int idir) const;

    // Get atoms
    std::vector<std::array<double,5>> get_atoms() const;

    // Shift atoms
    std::vector<std::array<double,5>> shift_atoms(double aa,double bb,double cc);

private:

    // Sum (PM=+1) or subtract (PM=-1) two cube files
    Cube addsub(const Cube& cube,int pm) const;

    // Fist two lines of the Cube file (comments)
    std::string comment1, comment2;

    // Number of atoms
    unsigned int Natoms;

    // Origin
    std::array<double,3> origin;

    // Number of voxels
    long int Na, Nb, Nc;

    // Axis vectors
    std::array<double,3> a, b, c;

    // Atoms
    std::vector<std::array<double,5>> atoms;

    // Data
    std::vector<double> data;

};

#endif
