#include <iostream>
#include <string>
#include <array>
#include <vector>

#ifndef CUBE_H
#define CUBE_H

// Define a rank-3 tensor
typedef std::vector<std::vector<std::vector<double>>> Matrix;

class Cube
{
public:
    // Default constructor (use copy_header to compy the header of a Cube and fill data with zeros)
    Cube();
    // Create cube file from data
    Cube(std::string fname);

    // Load CUbe fro file
    void load(std::string filename);

    // Printing routines (whole cube, only header or only data)
    void print(std::ostream& out) const;
    void print_header(std::ostream& out) const;
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

    // Return reshaped DATA (rank-3 tensor instead of vector)
    Matrix reshape() const;

    // Return Cube file origin
    std::array<double,3> get_origin() const;

    // Length of the voxel along a, b or c
    double da() const;
    double db() const;
    double dc() const;

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
