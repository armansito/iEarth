/*!
   @file   CS123Vector.h
   @author Travis Fischer (fisch0920@gmail.com)
   @date   Fall 2008

   @brief
      Provides basic functionality for a constant-sized Vector. DO NOT INCLUDE
      THIS FILE DIRECTLY! Instead, include <CS123Algebra.h>.
**/

#ifndef __CS123_VECTOR_H__
#define __CS123_VECTOR_H__

#include "CS123Algebra.h"
#include "CS123Matrix.h"
#include <ostream>
#include <limits>

#define CS123_VECTOR_NO_ELEMENTS    (N)
#define CS123_VECTOR_SIZE           (sizeof(T) * CS123_VECTOR_NO_ELEMENTS)

#define SQ(x) (x)*(x)

template<typename T = REAL>
struct vec2 {

///@name Constructors
//@{-----------------------------------------------------------------

    vec2<T>() {}
    vec2<T>(T v0, T v1) : x(v0), y(v1) {}
    vec2<T>(const vec2<T> &copy) : x(copy.x), y(copy.y) {}

    inline void init(T X, T Y) { x=X, y=Y;}
    static vec2<T> zero() { return vec2<T>(0, 0); }

//@}-----------------------------------------------------------------
///@name Operators
//@{-----------------------------------------------------------------

#define VECOP_PCW(op) { x op rhs.x; y op rhs.y; return *this; }
#define VECOP_SCA(op) { x op rhs;   y op rhs  ; return *this; }
#define X vec2

/*

These vector operations are used in all other vector classes, so we use the compiler
to make all the vector operations generic enough that they can be used with specific
classes. We could use template classes, but that would not allow us to access vectors
by vector.x, vector.y, vector.z, etc. Thus, we are forced to declare the structures
separately.

*/

#define VECTOR_OPS  \
    inline X& operator  = (const X& rhs) VECOP_PCW( =) /*<<< equality assignment */ \
    inline X& operator += (const X& rhs) VECOP_PCW(+=) /*<<< piecewise addition operator */ \
    inline X& operator -= (const X& rhs) VECOP_PCW(-=) /*<<< piecewise subtraction operator */ \
    inline X& operator *= (const X& rhs) VECOP_PCW(*=) /*<<< piecewise multiplication operator */ \
    inline X& operator /= (const X& rhs) VECOP_PCW(/=) /*<<< piecewise division operator */ \
     \
    inline X  operator  + (const X& rhs) const { return X(*this) += rhs; } /*<<< piecewise addition */ \
    inline X  operator  - (const X& rhs) const { return X(*this) -= rhs; } /*<<< piecewise subtraction */ \
    inline X  operator  * (const X& rhs) const { return X(*this) *= rhs; } /*<<< piecewise multiplication */ \
    inline X  operator  / (const X& rhs) const { return X(*this) /= rhs; } /*<<< piecewise division */ \
     \
    inline X& operator += (const T  rhs)  VECOP_SCA(+=) /*<<< scalar addition operator */ \
    inline X& operator -= (const T  rhs)  VECOP_SCA(-=) /*<<< scalar subtraction operator */ \
    inline X& operator *= (const T  rhs)  VECOP_SCA(*=) /*<<< scalar multiplication operator */ \
    inline X& operator /= (const T  rhs)  VECOP_SCA(/=) /*<<< scalar division operator */ \
     \
    inline X  operator  + (const T  rhs) const { return X(*this) += rhs; } /*<<< piecewise addition */ \
    inline X  operator  - (const T  rhs) const { return X(*this) -= rhs; } /*<<< piecewise subtraction */ \
    inline X  operator  * (const T  rhs) const { return X(*this) *= rhs; } /*<<< piecewise multiplication */ \
    inline X  operator  / (const T  rhs) const { return X(*this) /= rhs; } /*<<< piecewise multiplication */ \

    VECTOR_OPS

    //! Equality operator
    inline bool operator==(const X &rhs) { return (x == rhs.x && y == rhs.y); }

    //! Inequality operator
    inline bool operator!=(const X &rhs) { return (x != rhs.x || y != rhs.y); }


#undef X
#undef VECOP_PCW
#undef VECOP_SCA

//@}-----------------------------------------------------------------
///@name Additional Operations
//@{-----------------------------------------------------------------

//@}-----------------------------------------------------------------

    union {
        T data[2];
        struct { T x, y; };
    };


};

template<typename T = REAL>
struct vec3  {

///@name Constructors
//@{-----------------------------------------------------------------

    vec3(T v0 = 0, T v1 = 0, T v2 = 0) : x(v0), y(v1), z(v2) { }
    vec3(T *data) { x = data[0]; y = data[1]; z = data[2]; }

    inline void init(T X, T Y, T Z) { x=X, y=Y, z=Z; }
    static inline vec3 zero() { return vec3(0,0,0); }

//@}-----------------------------------------------------------------
///@name Operators
//@{-----------------------------------------------------------------

#define VECOP_PCW(op) { x op rhs.x; y op rhs.y; z op rhs.z; return *this; }
#define VECOP_SCA(op) { x op rhs;   y op rhs  ; z op rhs  ; return *this; }
#define X vec3

    VECTOR_OPS /* include the standard vector operations */

    //! Equality operator
    inline bool operator==(const X &rhs) { return (x == rhs.x && y == rhs.y && z == rhs.z); }

    //! Inequality operator
    inline bool operator!=(const X &rhs) { return (x != rhs.x || y != rhs.y || z != rhs.z); }


#undef X
#undef VECOP_PCW
#undef VECOP_SCA

//@}-----------------------------------------------------------------
///@name Additional Operations
//@{-----------------------------------------------------------------

    inline T normalize()                          { T m = getMagnitude(); x /= m, y /= m, z /= m; return m; }

    inline bool isZero()                    const { return EQ(x,0) && EQ(y,0) && EQ(z,0); }
    inline vec3 getNormalized()             const { T m = getMagnitude(); return vec3(x/m, y/m, z/m); }
    inline T getMagnitude()                 const { return sqrt(getMagnitude2()); }
    inline T getMagnitude2()                const { return x*x + y*y + z*z; }

    inline T getDistance(const vec3 &rhs)   const { return sqrt(getDistance2(rhs)); }
    inline T getDistance2(const vec3 &rhs)  const { return SQ(rhs.x - x) + SQ(rhs.y - y) + SQ(rhs.z - z); }

    inline T dot(const vec3 &rhs)           const { return x*rhs.x + y*rhs.y + z*rhs.z; }
    inline vec3 cross(const vec3& rhs)      const;

    /**
       Assuming *this is incident to the surface and the result is pointing
       away from the surface.
    **/
    inline vec3 reflectVector(const vec3 &normal) const;
    inline vec3 refractVector(const vec3 &normal, T in, T out) const;

//@}-----------------------------------------------------------------

    union {
        T data[3];
        struct {
            T x, y, z;
        };
    };

};


template<typename T>
struct vec4 {
#define vec4_T vec4<T>

///@name Constructors
//@{-----------------------------------------------------------------

    inline vec4_T() : x(0), y(0), z(0), w(0) {}
    inline vec4_T(T v0, T v1, T v2, T v3) : x(v0), y(v1), z(v2), w(v3) {}
    inline vec4_T(const T *data)    { x = data[0]; y = data[1]; z = data[2]; w = data[3]; }

    inline void init(T X, T Y, T Z, T W) { x=X, y=Y, z=Z, w=W; }
    static inline vec4_T zero()     { return vec4_T(0,0,0,0); }

//@}-----------------------------------------------------------------
///@name Operators
//@{-----------------------------------------------------------------

#define VECOP_PCW(op) { x op rhs.x; y op rhs.y; z op rhs.z; w op rhs.w; return *this; }
#define VECOP_SCA(op) { x op rhs  ; y op rhs  ; z op rhs  ; w op rhs  ; return *this; }
#define X vec4_T

    VECTOR_OPS /* include the standard vector operations */

    //! Equality operator
    inline bool operator==(const X &rhs) { return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w); }

    //! Inequality operator
    inline bool operator!=(const X &rhs) { return (x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w); }

#undef X
#undef VECOP_PCW
#undef VECOP_SCA

//@}-----------------------------------------------------------------
///@name Additional Operations
//@{-----------------------------------------------------------------

    inline vec4_T& homogenize()     { x /= w, y /= w, z /= w, w = 1; return *this; }
    inline vec4_T& unhomgenize()    { w = 0; return *this; }
    //inline T max()                  const { return qMax(qMax(qMax(x, y), z), w); }
    inline T dot(const vec4_T &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w; }

    inline T normalize();

    inline vec4_T getNormalized() const {
            T m = 1.0 / sqrt(x*x + y*y + z*z + w*w);
            return vec4_T(x*m, y*m, z*m, w*m);
    }

    inline T getMagnitude() const {
            return sqrt(getMagnitude2());
    }

    inline T getMagnitude2() const {
            return x * x + y * y + z * z + w * w;
    }

    inline T getDistance(const vec4_T &rhs) const {
            return sqrt(getDistance2(rhs));
    }

    inline T getDistance2(const vec4_T &rhs) const {
            return (rhs.x - x) * (rhs.x - x) + (rhs.y - y) * (rhs.y - y) +
                    (rhs.z - z) * (rhs.z - z) + (rhs.w - w) * (rhs.w - w);
    }

    inline vec4_T getHomogenized() {
        return vec4_T(*this).homogenize();
    }

    inline vec4_T cross(const vec4_T& rhs) const {
            return vec4_T(data[1] * rhs.data[2] - data[2] * rhs.data[1],
                           data[2] * rhs.data[0] - data[0] * rhs.data[2],
                           data[0] * rhs.data[1] - data[1] * rhs.data[0], 0);
    }

//@}-----------------------------------------------------------------

    union {
        T data[4];
        struct {
            T x, y, z, w;
        };
    };
};

#define Vector2 vec2<REAL>
#define Vector3 vec3<REAL>
#define Vector4 vec4<REAL>



/* Include inline implementations */
#include "CS123Vector.inl"

#endif // __CS123_VECTOR_H__

