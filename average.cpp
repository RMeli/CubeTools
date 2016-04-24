#include "average.h"

std::vector<std::array<double,2>> planar_average(Cube const& c,int idir)
{
    if( (idir < 1) or (idir > 3))
    {
        std::cerr << "ERROR: Invalid IDIR." << std::endl;
        std::cerr << "       IDIR should be 1 (x), 2 (y) or 3 (z)" << std::endl;

        std::exit(-1);
    }

    // Extract data from cube as rank-3 tensor
    Matrix data(c.reshape());

    std::array<double,3> o(c.get_origin());

    // Compute number of elements for each direction (number of voxels)
    unsigned int Na(data.size());
    unsigned int Nb(data[0].size());
    unsigned int Nc(data[0][0].size());

    std::vector<std::array<double,2>> pa;

    if(idir == 1)
    {
        // Lenght of each voxel along IDIR=1
        double d(c.da());

        // Allocate memory for planar average
        pa.resize(Na,std::array<double,2>{{0.0,0.0}});

        // Compute the planar average along i
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

            // Compute average (divide A by the total number of voxels in plane i)
            pa[i][1] = a / (Nb * Nc);
        }
    }

    if(idir == 2)
    {
        // Lenght of each voxel along IDIR=1
        double d(c.db());

        // Allocate memory for planar average
        pa.resize(Nb,std::array<double,2>{{0.0,0.0}});

        // Compute the planar average along i
        for(unsigned int j(0); j < Nb; j++)
        {
            double a(0);

            for(unsigned int i(0); i < Na; i++)
            {
                for(unsigned int k(0); k < Nc; k++)
                {
                    // Sum all the element of plane i
                    a += data[i][j][k];
                }
            }

            // Compute coordinate
            pa[j][0] = j * d + o[1];

            // Compute average (divide A by the total number of voxels in plane i)
            pa[j][1] = a / (Na * Nc);
        }
    }

    if(idir == 3)
    {
        // Lenght of each voxel along IDIR=1
        double d(c.dc());

        // Allocate memory for planar average
        pa.resize(Nc,std::array<double,2>{{0.0,0.0}});

        // Compute the planar average along i
        for(unsigned int k(0); k < Nc; k++)
        {
            double a(0);

            for(unsigned int i(0); i < Na; i++)
            {
                for(unsigned int j(0); j < Nb; j++)
                {
                    // Sum all the element of plane i
                    a += data[i][j][k];
                }
            }

            // Compute coordinate
            pa[k][0] = k * d + o[2];

            // Compute average (divide A by the total number of voxels in plane i)
            pa[k][1] = a / (Na * Nb);
        }
    }

    return pa;
}
