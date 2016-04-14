#include <iostream>
#include <string>
#include <array>
#include <vector>

class Cube
{
public:
    Cube(std::string fname);

    void print(std::ostream& out);
    void print_header(std::ostream& out);
    void print_data(std::ostream& out,int lines=0);

    bool compare_headers(Cube& cube,double threshold=1e-12);

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
