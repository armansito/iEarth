/*!
   N-length CS123Vector called rows which has been defined as:

   CS123Vector<N, T> rows[M];

**/

#ifndef __CS123_MATRIX_INL__
#define __CS123_MATRIX_INL__

#include "CS123Algebra.h"
#include <assert.h>
#include <math.h>

#include <iostream>
using namespace std;

template<typename T>
mat4<T> mat4<T>::identity() {
    return mat4<T>(1,0,0,0,
                   0,1,0,0,
                   0,0,1,0,
                   0,0,0,1);
}

template<typename T>
mat4<T> mat4<T>::transpose(const mat4<T> &m) {
    return mat4<T>(m.a, m.e, m.i, m.m,
                   m.b, m.f, m.j, m.n,
                   m.c, m.g, m.k, m.o,
                   m.d, m.h, m.l, m.p);
}

// Extra operators where Matrix is on right-hand side
// -----------------------------------------------------

//! 1xM row vector * MxN matrix yields a 1xN vector
template <typename T>
inline vec4<T> operator* (const vec4<T> &lhs, const mat4<T> &rhs) {
   return vec4<T>(rhs.m*lhs.w+rhs.a*lhs.x+rhs.e*lhs.y+rhs.i*lhs.z,
                  rhs.n*lhs.w+rhs.b*lhs.x+rhs.f*lhs.y+rhs.j*lhs.z,
                  rhs.o*lhs.w+rhs.c*lhs.x+rhs.g*lhs.y+rhs.k*lhs.z,
                  rhs.p*lhs.w+rhs.d*lhs.x+rhs.h*lhs.y+rhs.l*lhs.z);
}

//! @returns the MxN matrix resulting from multiplying a scalar by an MxN matrix
template <typename T>
inline mat4<T> operator* (const T &scale, const mat4<T> &rhs) {
    return rhs * scale; }

//! Prints a Matrix to an output stream
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const mat4<T> &m) {
    os << "[ ";
    for(unsigned j = 0; j < 4; ++j) {
        if(j) os << endl;
        os << "[ ";
        for(unsigned i = 0; i < 4; ++i)
            os << m.data[i + j*4] << " ";
        os << "]";
    }
    os << " ]";
    return os;
}

#if 0
//! @returns the transpose of this matrix
template <unsigned M, unsigned N, typename T>
const mat4<T> mat4<T>::getTranspose() const {
   assert(M == N);
   T temp[M * N];

   for(unsigned i = M; i--;)
      for(unsigned j = N; j--;)
         temp[i * N + j] = (*this)[j][i];

   return CS123Matrix<M, N, T>(temp);
}
#endif

#endif // __CS123_MATRIX_INL__

