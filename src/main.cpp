#include <iostream>

#include <awm/Matrix.hpp>

int main() {

    using namespace awm;

    Matrix<float, 2, 2> m(-1);

    std::cout <<
        m.data()[0]
        << " " <<
        m.data()[1]
        << "\n" <<
        m.data()[2]
        << " " <<
        m.data()[3]
    << std::endl << std::endl;

    m.at(0, 1) = 42;
    m[0][0] = 1337;
    auto row = m[1];
    row[0] = -100;
    row[1] = 666;

    std::cout <<
        m.data()[0]
        << " " <<
        m.data()[1]
        << "\n" <<
        m.data()[2]
        << " " <<
        m.data()[3]
    << std::endl << std::endl;

    auto mr = m.switch_rows(0, 1);

    std::cout <<
        mr.data()[0]
        << " " <<
        mr.data()[1]
        << "\n" <<
        mr.data()[2]
        << " " <<
        mr.data()[3]
    << std::endl << std::endl;

    auto mt = m.transposed();

    std::cout <<
        mt.data()[0]
        << " " <<
        mt.data()[1]
        << "\n" <<
        mt.data()[2]
        << " " <<
        mt.data()[3]
    << std::endl << std::endl;

    auto md = mt.delete_row(1);

    std::cout <<
        md.data()[0]
        << " " <<
        md.data()[1]
    << std::endl << std::endl;

    auto mm = m.multiply_row<float>(0, 0.5);

    std::cout <<
        mm.data()[0]
        << " " <<
        mm.data()[1]
        << "\n" <<
        mm.data()[2]
        << " " <<
        mm.data()[3]
    << std::endl << std::endl;

    return 0;
}