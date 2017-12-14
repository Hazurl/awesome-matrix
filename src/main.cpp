#include <iostream>

#include <awm/Matrix.hpp>

int main() {

    using namespace awm;

    Matrix<float, 4, 4> m44(0.);
    m44.at(0, 0) = 1;
    m44.at(0, 1) = 2;
    m44.at(0, 2) = 3;
    m44.at(0, 3) = 6;

    m44.at(1, 0) = -2;
    m44.at(1, 1) = -3;
    m44.at(1, 2) = -4;
    m44.at(1, 3) = -5;

    m44.at(2, 0) = -3;
    m44.at(2, 1) = 4;
    m44.at(2, 2) = 5;
    m44.at(2, 3) = -6;

    m44.at(3, 0) = 4;
    m44.at(3, 1) = 5;
    m44.at(3, 2) = 6;
    m44.at(3, 3) = 7;

    std::cout << m44.determinant() << std::endl;

    Matrix<float, 2, 2> _m(-1);
    Matrix<float, 2, 2> m{
        -1, -3,
        -2, -1
    };

    std::cout <<
        m.data()[0]
        << " " <<
        m.data()[1]
        << "\n" <<
        m.data()[2]
        << " " <<
        m.data()[3]
    << std::endl << std::endl;

    std::cout << m.determinant() << std::endl;

    m.at(0, 1) = 42;
    m[0][0] = 1337;
    auto row = m[1];
    row[0] = -100;
    row[1] = 666;

    std::cout << m.determinant() << std::endl;

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

    auto ms = m.submatrix<1, 1>(0, 1);

    std::cout <<
        ms.data()[0]
    << std::endl << std::endl;

    auto mw = m.without(1, 1);

    std::cout <<
        mw.data()[0]
    << std::endl << std::endl;

    std::cout <<
        m.data()[0]
        << " " <<
        m.data()[1]
        << "\n" <<
        m.data()[2]
        << " " <<
        m.data()[3]
    << std::endl << std::endl;

    float f[4];
    m.write_to(f);
    std::cout <<
        f[0]
        << " " <<
        f[1]
        << "\n" <<
        f[2]
        << " " <<
        f[3]
    << std::endl << std::endl;

    f[2] = f[1] = 0.2f;
    m.read_from(f);

    std::cout <<
        m.data()[0]
        << " " <<
        m.data()[1]
        << "\n" <<
        m.data()[2]
        << " " <<
        m.data()[3]
    << std::endl << std::endl;

    Matrix<float, 0, 0> m0;

    return 0;
}