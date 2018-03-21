#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>
#include "Vector.h"

class Matrix{
public:
    Matrix(Vector * vec[], int n){
        vs.push_back(0);
        for(int i = 0 ; i < n ; i++){
            vs.push_back(new Vector(*vec[i]));
        }
    }
    // deep copy trio
    Matrix(Matrix const & m){
        vs.push_back(0);
        for(unsigned i = 1 ; i < vs.size() ; i++){
            vs.push_back( new Vector(*m.vs[i]));
        }
    }
    ~Matrix() {
        for (unsigned i=0; i< vs.size(); ++i)
            delete vs[i];
    }

    Matrix &operator = (Matrix const & m){
        if (this != &m) {
            for (unsigned i=0; i< vs.size(); ++i)
                delete vs[i];
            vs.clear();
            vs.push_back(0);
            for(unsigned i = 1 ; i < m.vs.size() ; i++){
                vs.push_back( new Vector(*m.vs[i]));
            }
        }
        return *this;
    }
    // accessors
    Vector &operator [] (int i) const{
        return *vs[i];
    }

    void swap(int i, int j) {
        Vector* t = vs[i];
        vs[i] = vs[j];
        vs[j] = t;

    }
    void pivot(unsigned r) {
        unsigned i=r;
        for (; i<=vs.size()-1; ++i)
            if (vs[i]->component(r) != 0)
                break;
        if (i != r && i <= vs.size()-1)
        swap(r, i);
    }
    void eliminateForward(unsigned i) {
        for (unsigned j=i+1; j <=vs.size()-1; ++j)
            (*this)[j].saxpy(-(*this)[j][i],(*this)[i]);
    }
    void forward() {
        for (unsigned i=1; i<=vs.size()-1; ++i) {
            pivot(i);
            (*this)[i].multiply(1/(*this)[i][i]);
            eliminateForward(i);
        }
    }
    int nRows() const {
        return vs.size()-1;
    }
    private:
    std::vector <Vector*> vs;

};

#endif // MATRIX_H_INCLUDED
