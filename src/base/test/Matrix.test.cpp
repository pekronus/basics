#include <base/Matrix.hpp>
#include <iostream>

using namespace pekronus;
int
main(int argc, char** argv)
{
    Matrix<float> A(3,3, 1.);
    A.dump(std::cout);
    std::cout << "------------------\n";
    A(1,2) = 5;
    A(2,1) = -1.0;
    A.dump(std::cout);
    std::cout << "------------------\n";
    A.transpose();
    A.dump(std::cout);
    std::cout << "------------------\n";
    std::vector<float> v(3, 1.0);
    std::vector<float> v0(3);
    
    A.multiply(v, v0);
    for (int i = 0; i < 3; ++i)
        std::cout << v0[i] << " ";
    std::cout << std::endl;
    std::cout << "------------------\n";
    A.resize(2,2,1.0);
    A.dump(std::cout);
    
}
