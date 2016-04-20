#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <utility>

#include "Cube.h"

Cube::Cube()
{}

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

void Cube::print(std::ostream& out) const
{
    print_header(out);
    print_data(out);
}

void Cube::print_header(std::ostream& out) const
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

void Cube::print_data(std::ostream& out,int lines) const
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

bool Cube::header_is_compatible(const Cube& cube,double threshold) const
{
    // Compare origin coordinate by coordinate
    for(unsigned int i(0); i < 3; i++)
    {
        if( std::abs(origin[i] - cube.origin[i]) > threshold )
        {
            return false;
        }
    }

    // Compare number of voxels in every direction
    if( (Na != cube.Na) || (Nb != cube.Nb) || (Nc != cube.Nc) )
    {
        return false;
    }

    // Compare axis A
    for(unsigned int i(0); i < 3; i++)
    {
        if( std::abs(a[i] - cube.a[i]) > threshold )
        {
            return false;
        }
    }

    // Compare axis B
    for(unsigned int i(0); i < 3; i++)
    {
        if( std::abs(b[i] - cube.b[i]) > threshold )
        {
            return false;
        }
    }

    // Compare axis C
    for(unsigned int i(0); i < 3; i++)
    {
        if( std::abs(c[i] - cube.c[i]) > threshold )
        {
            return false;
        }
    }

    return true;
}

bool Cube::header_is_equal(const Cube& cube,double threshold) const
{
    // Compare number of atoms
    if(Natoms != cube.Natoms)
    {
        return false;
    }

    // Compare origin, number of voxels and axis
    if( ! header_is_compatible(cube,threshold) )
    {
        return false;
    }

    // Compare atoms
    for(unsigned int i(0); i < Natoms; i++)
    {
        for(unsigned int j(0); j < 5; j++)
        {
            if( std::abs(atoms[i][j] - cube.atoms[i][j]) > threshold )
            {
                return false;
            }
        }
    }

    return true;
}

void Cube::copy_header(const Cube& cube)
{
    // Copy first two comment lines
    comment1 = cube.comment1;
    comment2 = cube.comment2;

    // Copy number of atoms and origin
    Natoms = cube.Natoms;
    origin = cube.origin;

    // Copy voxel properties
    Na = cube.Na;
    Nb = cube.Nb;
    Nc = cube.Nc;
    a = cube.a;
    b = cube.b;
    c = cube.c;

    // Copy atoms
    atoms = cube.atoms;

    // Total number of voxels
    unsigned long int Nvol(Na*Nb*Nc);

    // Resize data and initialize all elements to zero
    data.clear();
    data.resize(Nvol,0.0);

}

Cube Cube::operator+(const Cube& cube) const
{
    // Check if the headers of the two cube files (*THIS and CUBE) are compatible
    if( header_is_compatible(cube) )
    {
        // Check if the headers of the two cube files (*THIS and CUBE) are equal
        if( ! header_is_equal(cube) )
        {
            // Warn the user that the cube files contain different atoms and/or atomic positions
            std::cerr << "\nWARNING: Cube files contains different atoms or atomic positions." << std::endl;
            std::cerr << "         The header of the first Cube will be considered for the sum.\n" << std::endl;
        }
    }
    else // Cube file are not compatible and can't be summed (TODO: origin shift)
    {
        std::cerr << "\nERROR: Cube files are not compatible.\n" << std::endl;

        std::exit(-1);
    }

    // Create empty cube file
    Cube sum;

    // Copy current header to new cube file
    sum.copy_header(*this);

    // Total number of voxels
    unsigned long int Nvol(Na*Nb*Nc);

    // Preallocate data of new cube file
    sum.data.resize(Nvol);

    // Sum voxel by voxel
    for(unsigned long int i(0); i < Nvol; i++)
    {
        sum.data[i] = data[i] + cube.data[i];
    }

    return sum;
}
