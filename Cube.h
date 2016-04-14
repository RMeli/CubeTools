#include <string>
#include <array>
#include <vector>

class Cube
{
public:
    Cube(std::string fname);

private:
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