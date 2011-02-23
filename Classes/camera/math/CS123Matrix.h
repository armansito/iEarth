/*!
   @brief
      Provides basic functionality for a templated, arbitrarily-sized matrix.
      DO NOT INCLUDE THIS FILE DIRECTLY! Instead, include <CS123Algebra.h>.
**/

#ifndef __CS123_MATRIX_H__
#define __CS123_MATRIX_H__

#include "CS123Vector.h"
#include "CS123Algebra.h"
#include <memory.h>
#include <math.h>
#include <ostream>

#define CS123_MATRIX_NO_ELEMENTS    (M * N)
#define CS123_MATRIX_SIZE           (sizeof(T) * CS123_MATRIX_NO_ELEMENTS)


template<typename T = REAL>
struct mat4 {
    mat4<T>( T _00 = 0, T _01 = 0, T _02 = 0, T _03 = 0,
             T _10 = 0, T _11 = 0, T _12 = 0, T _13 = 0,
             T _20 = 0, T _21 = 0, T _22 = 0, T _23 = 0,
             T _30 = 0, T _31 = 0, T _32 = 0, T _33 = 0 ){
        data[0] = _00;        data[1] = _01;        data[2] = _02;        data[3] = _03;
        data[4] = _10;        data[5] = _11;        data[6] = _12;        data[7] = _13;
        data[8] = _20;        data[9] = _21;        data[10] = _22;       data[11] = _23;
        data[12] = _30;       data[13] = _31;       data[14] = _32;       data[15] = _33;
    }

    mat4<T>(const T *copy)                 { memcpy(data, copy,      sizeof(T) * 16); }
    mat4<T>(const mat4<T> &copy)           { memcpy(data, copy.data, sizeof(T) * 16); }
    mat4<T>& operator=(const mat4<T> &rhs) { memcpy(data, rhs.data,  sizeof(T) * 16); return *this; }

    inline void fillArray(T* dest) const   { memcpy(dest, data,      sizeof(T) * 16); }

    inline       T& get(int row, int col)       { return data[row * 4 + col]; }
    inline const T& get(int row, int col) const { return data[row * 4 + col]; }

    static mat4<T> identity();
    static mat4<T> transpose(const mat4<T> &m);

    inline mat4<T> getTranspose() const { return mat4<T>::transpose(*this); }

    inline mat4& operator+=(const mat4& rhs) {
        for (unsigned i = 0; i < 16; ++i)
            data[i] += rhs.data[i];
        return *this;
    }

    inline mat4& operator-=(const mat4& rhs) {
        for (unsigned i = 0; i < 16; ++i)
            data[i] -= rhs.data[i];
        return *this;
    }

    inline mat4 operator-(const mat4 &rhs) {
            return mat4(*this) -= rhs;
    }

    inline mat4 operator+(const mat4 &rhs) {
            return mat4(*this) += rhs;
    }

    inline mat4& operator*=(const T rhs) {
            data[0] *= rhs;
            data[1] *= rhs;
            data[2] *= rhs;
            data[3] *= rhs;
            data[4] *= rhs;
            data[5] *= rhs;
            data[6] *= rhs;
            data[7] *= rhs;
            data[8] *= rhs;
            data[9] *= rhs;
            data[10] *= rhs;
            data[11] *= rhs;
            data[12] *= rhs;
            data[13] *= rhs;
            data[14] *= rhs;
            data[15] *= rhs;
            return *this;
    }

    inline Vector4 operator*(const Vector4 &rhs) const {
        return Vector4( a*rhs.x + b*rhs.y + c*rhs.z + d*rhs.w,
                        e*rhs.x + f*rhs.y + g*rhs.z + h*rhs.w,
                        i*rhs.x + j*rhs.y + k*rhs.z + l*rhs.w,
                        m*rhs.x + n*rhs.y + o*rhs.z + p*rhs.w );
    }

    inline void mulVec4(const Vector4 &rhs, Vector4 &out) {
        out.data[0] = a*rhs.x + b*rhs.y + c*rhs.z + d*rhs.w;
        out.data[1] = e*rhs.x + f*rhs.y + g*rhs.z + h*rhs.w;
        out.data[2] = i*rhs.x + j*rhs.y + k*rhs.z + l*rhs.w;
        out.data[3] = m*rhs.x + n*rhs.y + o*rhs.z + p*rhs.w;
    }

    inline mat4& operator/=(const T rhs) {
            data[0] /= rhs;
            data[1] /= rhs;
            data[2] /= rhs;
            data[3] /= rhs;
            data[4] /= rhs;
            data[5] /= rhs;
            data[6] /= rhs;
            data[7] /= rhs;
            data[8] /= rhs;
            data[9] /= rhs;
            data[10] /= rhs;
            data[11] /= rhs;
            data[12] /= rhs;
            data[13] /= rhs;
            data[14] /= rhs;
            data[15] /= rhs;
            return *this;
    }

    inline mat4 operator/(const T rhs) {
            return mat4(*this) /= rhs;
    }



    inline mat4 getInverse() const {
            return mat4(*this).invert();
    }

    inline T getDeterminant() {
        return a*f*k*p-a*f*l*o-a*g*j*p+a*g*l*n+a*h*j*o-a*h*k*n-b*e*k*p+b*e*l*o+b*g*i*p-b*g*l*m-b*h*i*o+b*h*k*m+c*e*j*p-c*e*l*n-c*f*i*p+c*f*l*m+c*h*i*n-c*h*j*m-d*e*j*o+d*e*k*n+d*f*i*o-d*f*k*m-d*g*i*n+d*g*j*m;
    }

    inline mat4& invert() {
         T det = getDeterminant(),
                _00 = (f*k*p+g*l*n+h*j*o-f*l*o-g*j*p-h*k*n)/det,
                _01 = (b*l*o+c*j*p+d*k*n-b*k*p-c*l*n-d*j*o)/det,
                _02 = (b*g*p+c*h*n+d*f*o-b*h*o-c*f*p-d*g*n)/det,
                _03 = (b*h*k+c*f*l+d*g*j-b*g*l-c*h*j-d*f*k)/det,
                _10 = (e*l*o+h*k*m+g*i*p-e*k*p-g*l*m-h*i*o)/det,
                _11 = (a*k*p+c*l*m+d*i*o-a*l*o-c*i*p-d*k*m)/det,
                _12 = (a*h*o+c*e*p+d*g*m-a*g*p-c*h*m-d*e*o)/det,
                _13 = (a*g*l+c*h*i+d*e*k-a*h*k-c*e*l-d*g*i)/det,
                _20 = (e*j*p+f*l*m+h*i*n-e*l*n-f*i*p-h*j*m)/det,
                _21 = (a*l*n+b*i*p+d*j*m-a*j*p-b*l*m-d*i*n)/det,
                _22 = (a*f*p+b*h*m+d*e*n-a*h*n-b*e*p-d*f*m)/det,
                _23 = (a*h*j+b*e*l+d*f*i-a*f*l-b*h*i-d*e*j)/det,
                _30 = (e*k*n+f*i*o+g*j*m-e*j*o-f*k*m-g*i*n)/det,
                _31 = (a*j*o+b*k*m+c*i*n-a*k*n-b*i*o-c*j*m)/det,
                _32 = (a*g*n+b*e*o+c*f*m-a*f*o-b*g*m-c*e*n)/det,
                _33 = (a*f*k+b*g*i+c*e*j-a*g*j-b*e*k-c*f*i)/det;
         a = _00;
         b = _01;
         c = _02;
         d = _03;
         e = _10;
         f = _11;
         g = _12;
         h = _13;
         i = _20;
         j = _21;
         k = _22;
         l = _23;
         m = _30;
         n = _31;
         o = _32;
         p = _33;
         return *this;
    }

    inline mat4& operator*=(const mat4 &rhs) {
            T _00 = data[0]  * rhs.data[0] + data[1]  * rhs.data[4] + data[2]  * rhs.data[8]  + data[3]  * rhs.data[12];
            T _01 = data[0]  * rhs.data[1] + data[1]  * rhs.data[5] + data[2]  * rhs.data[9]  + data[3]  * rhs.data[13];
            T _02 = data[0]  * rhs.data[2] + data[1]  * rhs.data[6] + data[2]  * rhs.data[10] + data[3]  * rhs.data[14];
            T _03 = data[0]  * rhs.data[3] + data[1]  * rhs.data[7] + data[2]  * rhs.data[11] + data[3]  * rhs.data[15];

            T _10 = data[4]  * rhs.data[0] + data[5]  * rhs.data[4] + data[6]  * rhs.data[8]  + data[7]  * rhs.data[12];
            T _11 = data[4]  * rhs.data[1] + data[5]  * rhs.data[5] + data[6]  * rhs.data[9]  + data[7]  * rhs.data[13];
            T _12 = data[4]  * rhs.data[2] + data[5]  * rhs.data[6] + data[6]  * rhs.data[10] + data[7]  * rhs.data[14];
            T _13 = data[4]  * rhs.data[3] + data[5]  * rhs.data[7] + data[6]  * rhs.data[11] + data[7]  * rhs.data[15];

            T _20 = data[8]  * rhs.data[0] + data[9]  * rhs.data[4] + data[10] * rhs.data[8]  + data[11] * rhs.data[12];
            T _21 = data[8]  * rhs.data[1] + data[9]  * rhs.data[5] + data[10] * rhs.data[9]  + data[11] * rhs.data[13];
            T _22 = data[8]  * rhs.data[2] + data[9]  * rhs.data[6] + data[10] * rhs.data[10] + data[11] * rhs.data[14];
            T _23 = data[8]  * rhs.data[3] + data[9]  * rhs.data[7] + data[10] * rhs.data[11] + data[11] * rhs.data[15];

            T _30 = data[12] * rhs.data[0] + data[13] * rhs.data[4] + data[14] * rhs.data[8]  + data[15] * rhs.data[12];
            T _31 = data[12] * rhs.data[1] + data[13] * rhs.data[5] + data[14] * rhs.data[9]  + data[15] * rhs.data[13];
            T _32 = data[12] * rhs.data[2] + data[13] * rhs.data[6] + data[14] * rhs.data[10] + data[15] * rhs.data[14];
            T _33 = data[12] * rhs.data[3] + data[13] * rhs.data[7] + data[14] * rhs.data[11] + data[15] * rhs.data[15];

            data[0] = _00;
            data[1] = _01;
            data[2] = _02;
            data[3] = _03;
            data[4] = _10;
            data[5] = _11;
            data[6] = _12;
            data[7] = _13;
            data[8] = _20;
            data[9] = _21;
            data[10] = _22;
            data[11] = _23;
            data[12] = _30;
            data[13] = _31;
            data[14] = _32;
            data[15] = _33;
            return *this;
    }

    inline mat4 operator*(const mat4& rhs) const {
            return mat4(*this) *= rhs;
    }

    inline mat4 operator*(const T rhs) const {
            return mat4(*this) *= rhs;
    }

    union {
        T data[16];
        struct {
            T a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
        };
    };
};


typedef mat4<REAL> Matrix4x4;


/* Include inline implementations */
#include "CS123Matrix.inl"

/* The following global functions are not templated, so they will be found in
 * CS123Matrix.cpp
 */

///@name Routines which generate specific-purpose transformation matrices
//@{-----------------------------------------------------------------------------

/// @returns the scale matrix described by the vector
extern Matrix4x4 getScaleMat(const Vector4 &v);
/// @returns the translation matrix described by the vector
extern Matrix4x4 getTransMat(const Vector4 &v);
/// @returns the rotation matrix about the x axis by the specified angle
extern Matrix4x4 getRotXMat (const REAL radians);
/// @returns the rotation matrix about the y axis by the specified angle
extern Matrix4x4 getRotYMat (const REAL radians);
/// @returns the rotation matrix about the z axis by the specified angle
extern Matrix4x4 getRotZMat (const REAL radians);
/// @returns the rotation matrix around the vector and point by the specified angle
extern Matrix4x4 getRotMat  (const Vector4 &p, const Vector4 &v, const REAL a);

//@}-----------------------------------------------------------------------------
///@name Routines which generate specific-purpose inverse transformation matrices
//@{-----------------------------------------------------------------------------

/// @returns the inverse scale matrix described by the vector
extern Matrix4x4 getInvScaleMat(const Vector4 &v);
/// @returns the inverse translation matrix described by the vector
extern Matrix4x4 getInvTransMat(const Vector4 &v);
/// @returns the inverse rotation matrix about the x axis by the specified angle
extern Matrix4x4 getInvRotXMat (const REAL radians);
/// @returns the inverse rotation matrix about the y axis by the specified angle
extern Matrix4x4 getInvRotYMat (const REAL radians);
/// @returns the inverse rotation matrix about the z axis by the specified angle
extern Matrix4x4 getInvRotZMat (const REAL radians);
/// @returns the inverse rotation matrix around the vector and point by the specified angle
extern Matrix4x4 getInvRotMat  (const Vector4 &p, const Vector4 &v, const REAL a);

//@}-----------------------------------------------------------------------------


#endif // __CS123_MATRIX_H__

