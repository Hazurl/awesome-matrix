#pragma once



#include <memory>

namespace awm {

template<typename T>
class IMatrix {
private:

    using cr_value = std::conditional_t<(sizeof(T) > 8), const T&, T>;

    template<typename M>
    struct AbstractMatrix : public BaseMatrix {
        M& m;
        AbstractMatrix(M& m) : m(m) {}

        virtual T&       at(unsigned int r, unsigned int c) & { return m.at(r, c); }
        virtual cr_value at(unsigned int r, unsigned int c) const & { return m.at(r, c); }
        virtual T        at(unsigned int r, unsigned int c) const && { return m.at(r, c); }

        virtual T&       operator () (unsigned int r, unsigned int c) & { return m(r, c); }
        virtual cr_value operator () (unsigned int r, unsigned int c) const & { return m(r, c); }
        virtual T        operator () (unsigned int r, unsigned int c) const && { return m(r, c); }

        virtual T* data () & { return m.data(); }
        virtual const T* data () const& { return m.data(); }

        virtual unsigned int row() const { return m.row(); }
        virtual unsigned int column() const { return m.column(); }
        unsigned int size() const { return row() * column(); }
        bool in_range(unsigned int r, unsigned int c) const { return r < row() && c < column(); }
    };

    struct BaseMatrix {
        virtual T&       at(unsigned int r, unsigned int c) & = 0;
        virtual cr_value at(unsigned int r, unsigned int c) const & = 0;
        virtual T        at(unsigned int r, unsigned int c) const && = 0;

        virtual T&       operator () (unsigned int r, unsigned int c) & = 0;
        virtual cr_value operator () (unsigned int r, unsigned int c) const & = 0;
        virtual T        operator () (unsigned int r, unsigned int c) const && = 0;

        virtual T* data () & = 0;
        virtual const T* data () const& = 0;

        virtual unsigned int row() const = 0;
        virtual unsigned int column() const = 0;
        unsigned int size() const { return row() * column(); }
        bool in_range(unsigned int r, unsigned int c) const { return r < row() && c < column(); }
    };

public:

    template<typename M>
    IMatrix(M const& m) : base(std::make_unique<AbstractMatrix<M>>(m)) {}

private:

    std::unique_ptr<BaseMatrix> base;

};

}