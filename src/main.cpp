#include <iostream>

#include <awm/Matrix.hpp>

int main() {

    using namespace awm;

    Matrix<float, 2, 2> m;

    m.at(0, 1) = 42;
    m[0][0] = 1337;

    std::cout <<
        ((float*)m)[1]
    << std::endl;


    return 0;
}