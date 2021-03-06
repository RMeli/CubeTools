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

#include <cmath>

#include "average.h"
#include "function.h"
#include "interpolation.h"

Table planar_average(Cube const& c,int idir)
{
    // Check IDIR value
    if( (idir < 1) or (idir > 3))
    {
        std::cerr << "ERROR: Invalid IDIR." << std::endl;
        std::cerr << "       IDIR should be 1 (x), 2 (y) or 3 (z)" << std::endl;

        std::exit(-1);
    }

    // Extract data from cube as rank-3 tensor
    // First index: direction A (x)
    // Second index: direction B (y)
    // Third index: direction C (z)
    Matrix data(c.reshape());

    // Extract origin
    std::array<double,3> o(c.get_origin());

    // Compute number of elements for each direction (number of voxels)
    unsigned int Na(data.size()); // Direction A (x)
    unsigned int Nb(data[0].size()); // Direction B (y)
    unsigned int Nc(data[0][0].size()); // Direction C (z)

    // Declare planar average table (empty)
    Table pa;

    if(idir == 1)
    {
        // Lenght of each voxel along IDIR=1
        double d(c.da());

        // Allocate memory for planar average
        pa.resize(Na,std::array<double,2>{{0.0,0.0}});

        // Loop over IDIR=1 (direction A)
        for(unsigned int i(0); i < Na; i++)
        {
            double a(0);

            for(unsigned int j(0); j < Nb; j++)
            {
                for(unsigned int k(0); k < Nc; k++)
                {
                    // Sum all the element of plane i
                    a += data[i][j][k];
                }
            }

            // Compute coordinate
            pa[i][0] = i * d + o[0];

            // Compute average (divide sum by the total number of voxels in plane i)
            pa[i][1] = a / (Nb * Nc);
        }
    }

    if(idir == 2)
    {
        // Lenght of each voxel along IDIR=1
        double d(c.db());

        // Allocate memory for planar average
        pa.resize(Nb,std::array<double,2>{{0.0,0.0}});

        // Loop over IDIR=2 (direction B)
        for(unsigned int j(0); j < Nb; j++)
        {
            double a(0);

            for(unsigned int i(0); i < Na; i++)
            {
                for(unsigned int k(0); k < Nc; k++)
                {
                    // Sum all the element of plane j
                    a += data[i][j][k];
                }
            }

            // Compute coordinate
            pa[j][0] = j * d + o[1];

            // Compute average (divide sum by the total number of voxels in plane j)
            pa[j][1] = a / (Na * Nc);
        }
    }

    if(idir == 3)
    {
        // Lenght of each voxel along IDIR=1
        double d(c.dc());

        // Allocate memory for planar average
        pa.resize(Nc,std::array<double,2>{{0.0,0.0}});

        // Loop over IDIR=3 (direction C)
        for(unsigned int k(0); k < Nc; k++)
        {
            double a(0);

            for(unsigned int i(0); i < Na; i++)
            {
                for(unsigned int j(0); j < Nb; j++)
                {
                    // Sum all the element of plane k
                    a += data[i][j][k];
                }
            }

            // Compute coordinate
            pa[k][0] = k * d + o[2];

            // Compute average (divide sum by the total number of voxels in plane k)
            pa[k][1] = a / (Na * Nb);
        }
    }

    return pa;
}

Table macro_average(Cube const& c,int idir, int m, double sigma)
{
    // Compute planar average
    Table pa( planar_average(c,idir) );

    if(m == -1)
    {
        // Fourier interpolation is not necessary
        m = pa.size();
    }

    // Increase the density of points of the planar average
    Table fpa( fourier_interpolation(pa,m) );

    // Total number of points
    uint N(fpa.size());

    // Macroscopic average
    Table ma(N,std::array<double,2>{0,0});

    double norm(0);
    double sum(0);
    double r(0);

    for(uint i(0); i < N; i++)
    {
        norm = 0;
        sum = 0;

        for(uint j(0); j < N; j++)
        {
            // TODO: Without PBC
            r = c.pbc(fpa[j][1] - fpa[i][1],idir);

            norm += gaussian_1d(r,0,sigma);
            sum += fpa[j][1] * norm;
        }

        // Coordinate along IDIR
        ma[i][0] = fpa[i][0];

        // Macroscopic average
        ma[i][1] = sum / norm;
    }

    return ma;
}


double total_average(Cube const& c)
{
    // Cube data (not reshaped)
    std::vector<double> data( c.get_data() );

    // Total number of voxels
    double N(data.size());

    // Sum over all data points
    double sum(0);

    for(unsigned int i(0); i < N; i++)
    {
        sum += data[i];
    }

    return sum / N;
}

double g_average(Cube const& c,std::array<double,3> R,std::array<double,3> sigma, bool pbc)
{
    // Cube data (not reshaped)
    Matrix data( c.reshape() );

    // Origin
    std::array<double,3> o(c.get_origin());

    // Compute number of elements for each direction (number of voxels)
    unsigned int Na(data.size());
    unsigned int Nb(data[0].size());
    unsigned int Nc(data[0][0].size());

    // Weighted sum over all data points
    double sum(0);

    // Sum of weights
    double weight(0);

    double da( c.da() );
    double db( c.db() );
    double dc( c.dc() );

    if( sigma[0] <= da)
    {
        std::cerr << "WARNING: Gaussian SD is possibly too small." << std::endl;
        std::cerr << "         The SD along a is smaller than da." << std::endl;
    }
    if( sigma[1] <= db)
    {
        std::cerr << "WARNING: Gaussian SD is possibly too small." << std::endl;
        std::cerr << "         The SD along b is smaller than db." << std::endl;
    }
    if( sigma[2] <= dc)
    {
        std::cerr << "WARNING: Gaussian SD is possibly too small." << std::endl;
        std::cerr << "         The SD along c is smaller than dc." << std::endl;
    }

    // Position
    std::array<double,3> r{{0,0,0}};

    // Distance
    std::array<double,3> d{{0,0,0}};

    double g(0);

    for(unsigned int i(0); i < Na; i++)
    {
        for(unsigned int j(0); j < Nb; j++)
        {
            for(unsigned int k(0); k < Nc; k++)
            {
                // Compute current position
                r[0] = i * da + o[0];
                r[1] = j * db + o[1];
                r[2] = k * dc + o[2];

                // Compute distance with respect to the gaussian center
                d[0] = r[0] - R[0];
                d[1] = r[1] - R[1];
                d[2] = r[2] - R[2];

                // Apply periodic boundary conditions
                if(pbc == true)
                {
                    d[0] = c.pbc(d[0],1);
                    d[1] = c.pbc(d[1],2);
                    d[2] = c.pbc(d[2],3);
                }

                // Compute weight (the average is 0 since d is already the r-R)
                g = gaussian_3d(d,{{0,0,0}},sigma);

                sum += data[i][j][k] * g;

                weight += g;
            }
        }
    }

    return sum / weight;
}
