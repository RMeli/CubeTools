#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "Cube.h"

Cube::Cube(std::string fname)
{
    // Open Cube file
    std::fstream in(fname);
    
    if( !in.is_open() )
    {
        std::cerr << "ERROR: Impossible to open cube file." << std::endl;
        std::exit(-1);
    }

    // Store first two comment lines
    std::getline(in,comment1);
    std::getline(in,comment2);
    
    // Number of atoms and origin
    in >> Natoms >> origin[0] >> origin[1] >> origin[2];
    
    // Voxel properties (number and axis)
    in >> Na >> a[0] >> a[1] >> a[2];
    in >> Nb >> b[0] >> b[1] >> b[2];
    in >> Nc >> c[0] >> c[1] >> c[2];
    
    // Preallocate vector for atoms
    atoms.resize(Natoms);
    
    // Store atoms
    for(unsigned int i(0); i < Natoms; i++)
    {
        // Store atom
        in >> atoms[i][0] >> atoms[i][1] >> atoms[i][2] >> atoms[i][3] >> atoms[i][4];
    }
    
    unsigned long int Nvol(Na*Nb*Nc);
    
    // Preallocate vector for volumetric data
    data.resize(Nvol);
    
    // Store volumetric data
    for(unsigned long int i(0); i < Nvol; i += 6)
    {
        in >> data[i] >> data[i+1] >> data[i+2] >> data[i+3] >> data[i+4] >> data[i+5];
    }
}