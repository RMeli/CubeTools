#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

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

    // Total number of voxels
    unsigned long int Nvol(Na*Nb*Nc);

    // Preallocate vector for volumetric data
    data.resize(Nvol);

    // Store volumetric data
    for(unsigned long int i(0); i < Nvol; i += 6)
    {
        in >> data[i] >> data[i+1] >> data[i+2] >> data[i+3] >> data[i+4] >> data[i+5];
    }
}

void Cube::print(std::ostream& out)
{
    print_header(out);
    print_data(out);
}

void Cube::print_header(std::ostream& out)
{
    // Print first two comment lines
    out << comment1 << std::endl;
    out << comment2 << std::endl;

    // Print number of atoms and origin
    out << std::setw(5) << Natoms;
    for(unsigned int i(0); i < 3; i++)
    {
        out << std::fixed <<std::setprecision(6) << std::setw(12) << origin[i];
    }
    out << std::endl;

    // Print voxel properties (number and axis): A
    out << std::setw(5) << Na;
    for(unsigned int i(0); i < 3; i++)
    {
        out << std::fixed <<std::setprecision(6) << std::setw(12) << a[i];
    }
    out << std::endl;

    // Print voxel properties (number and axis): B
    out << std::setw(5) << Nb;
    for(unsigned int i(0); i < 3; i++)
    {
        out << std::fixed <<std::setprecision(6) << std::setw(12) << b[i];
    }
    out << std::endl;

    // Print voxel properties (number and axis): C
    out << std::setw(5) << Nc;
    for(unsigned int i(0); i < 3; i++)
    {
        out << std::fixed <<std::setprecision(6) << std::setw(12) << c[i];
    }
    out << std::endl;

    // Print atoms
    for(unsigned int i(0); i < Natoms; i++)
    {
        out << std::fixed << std::setprecision(0) << std::setw(5)<< atoms[i][0];

        for(unsigned int j(1); j < 5; j++)
        {
            out << std::fixed << std::setprecision(6) << std::setw(12) << atoms[i][j];
        }

        out << std::endl;
    }
}

void Cube::print_data(std::ostream& out,int lines)
{
    // Total number of voxels
    unsigned long int Nvol(Na*Nb*Nc);

    // Voxel to print
    unsigned long int min(0);
    unsigned long int max(Nvol);

    if(lines < 0)
    {
        min = Nvol + lines * 6;
    }
    else if(lines > 0)
    {
        max = lines * 6;
    }

    // Print volumetric data
    for(unsigned int i(min); i < max; i++)
    {
        out << std::fixed << std::scientific << std::setprecision(5) << std::setw(13) << data[i];

        if( (i+1) % 6 == 0)
        {
            out << std::endl;
        }
    }
}
