/*!
   @file   CS123Matrix.cpp
   @author Travis Fischer (fisch0920@gmail.com)
   @date   Fall 2008
   
   @brief
      Provides basic functionality for a templated, arbitrarily-sized matrix.
      You will need to fill this file in for the Camtrans assignment.

**/

// CS123Matrix.h can be found in /course/cs123/include/algebra
#include "CS123Matrix.h"
#include <iostream>

//@name Routines which generate specific-purpose transformation matrices
//@{---------------------------------------------------------------------

// @returns the scale matrix described by the vector
Matrix4x4 getScaleMat(const Vector4 &v) {
    return Matrix4x4(v.x, 0, 0, 0,
                     0, v.y, 0, 0,
                     0, 0, v.z, 0,
                     0, 0, 0,   1);
}

// @returns the translation matrix described by the vector
Matrix4x4 getTransMat(const Vector4 &v) {
   return Matrix4x4(1, 0, 0, v.data[0],
                    0, 1, 0, v.data[1],
                    0, 0, 1, v.data[2],
                    0, 0, 0, 1);
}

// @returns the rotation matrix about the x axis by the specified angle
Matrix4x4 getRotXMat (const REAL radians) {
   const REAL cosTheta = cos(radians);
   const REAL sinTheta = sin(radians);

   return Matrix4x4(1, 0, 0, 0, 
                    0, cosTheta, -sinTheta, 0, 
                    0, sinTheta, cosTheta, 0, 
                    0, 0, 0, 1);
}

// @returns the rotation matrix about the y axis by the specified angle
Matrix4x4 getRotYMat (const REAL radians) {
   const REAL cosTheta = cos(radians);
   const REAL sinTheta = sin(radians);

   return Matrix4x4(cosTheta, 0, sinTheta, 0, 
                    0, 1, 0, 0, 
                    -sinTheta, 0, cosTheta, 0, 
                    0, 0, 0, 1);
}

// @returns the rotation matrix about the z axis by the specified angle
Matrix4x4 getRotZMat (const REAL radians) {
   const REAL cosTheta = cos(radians);
   const REAL sinTheta = sin(radians);

   return Matrix4x4(cosTheta, -sinTheta, 0, 0, 
                    sinTheta, cosTheta, 0, 0, 
                    0, 0, 1, 0, 
                    0, 0, 0, 1);
}

// @returns the rotation matrix around the vector and point by the specified angle
Matrix4x4 getRotMat  (const Vector4 &p, const Vector4 &v, const REAL a) {
   // Translate to origin from point p
   const REAL vZ = v.data[2];
   const REAL vX = v.data[0];
   const REAL theta = atan2(vZ, vX);
   const REAL phi   = -atan2(v.data[1], sqrt(vX * vX + vZ * vZ));
   
   const Matrix4x4 &transToOrigin   = getInvTransMat(Vector4(p.data[0], p.data[1], p.data[2], 0));
   const Matrix4x4 &A               = getRotYMat(theta);
   const Matrix4x4 &B               = getRotZMat(phi);
   const Matrix4x4 &C               = getRotXMat(a);
   const Matrix4x4 &invA            = getInvRotYMat(theta);
   const Matrix4x4 &invB            = getInvRotZMat(phi);
   const Matrix4x4 &transBack       = getTransMat(Vector4(p.data[0], p.data[1], p.data[2], 0));
   
   return transBack * invA * invB * C * B * A * transToOrigin;
}


// @returns the inverse scale matrix described by the vector
Matrix4x4 getInvScaleMat(const Vector4 &v) {
   if (v.data[0] != 0 && v.data[1] != 0 && v.data[2] != 0) {
      return Matrix4x4(1.0f / v.data[0], 0, 0, 0,
                       0, 1.0f / v.data[1], 0, 0,
                       0, 0, 1.0f / v.data[2], 0,
                       0, 0, 0, 1);
   }

   cerr << "\nError: " << "Divide by zero in getInvScaleMat()" << endl << endl; 
   return Matrix4x4();
}

// @returns the inverse translation matrix described by the vector
Matrix4x4 getInvTransMat(const Vector4 &v) {
   return Matrix4x4(1, 0, 0, -v.data[0],
                    0, 1, 0, -v.data[1],
                    0, 0, 1, -v.data[2],
                    0, 0, 0, 1);
}

// @returns the inverse rotation matrix about the x axis by the specified angle
Matrix4x4 getInvRotXMat (const REAL radians) {
   const REAL cosTheta = cos(radians);
   const REAL sinTheta = sin(radians);

   return Matrix4x4(1, 0, 0, 0, 
                    0, cosTheta, sinTheta, 0, 
                    0, -sinTheta, cosTheta, 0, 
                    0, 0, 0, 1);
}

// @returns the inverse rotation matrix about the y axis by the specified angle
Matrix4x4 getInvRotYMat (const REAL radians) {
   const REAL cosTheta = cos(radians);
   const REAL sinTheta = sin(radians);

   return Matrix4x4(cosTheta, 0, -sinTheta, 0, 
                    0, 1, 0, 0, 
                    sinTheta, 0, cosTheta, 0, 
                    0, 0, 0, 1);
}

// @returns the inverse rotation matrix about the z axis by the specified angle
Matrix4x4 getInvRotZMat (const REAL radians) {
   const REAL cosTheta = cos(radians);
   const REAL sinTheta = sin(radians);

   return Matrix4x4(cosTheta, sinTheta, 0, 0, 
                    -sinTheta, cosTheta, 0, 0, 
                    0, 0, 1, 0, 
                    0, 0, 0, 1);
}

// @returns the inverse rotation matrix around the vector and point by the specified angle
Matrix4x4 getInvRotMat  (const Vector4 &p, const Vector4 &v, const REAL a) {
   const REAL vZ = v.data[2];
   const REAL vX = v.data[0];
   const REAL theta = atan2(vZ, vX);
   const REAL phi   = -atan2(v.data[1], sqrt(vX * vX + vZ * vZ));
   
   const Matrix4x4 &transToOrigin = getInvTransMat(Vector4(p.data[0], p.data[1], p.data[2], 0));
   const Matrix4x4 &A = getRotYMat(theta);
   const Matrix4x4 &B = getRotZMat(phi);
   const Matrix4x4 &C = getRotXMat(a);
   const Matrix4x4 &invA = getInvRotYMat(theta);
   const Matrix4x4 &invB = getInvRotZMat(phi);
   const Matrix4x4 &transBack = getTransMat(Vector4(p.data[0], p.data[1], p.data[2], 0));
   
   return transBack * (invA * invB * C * B * A).getTranspose() * transToOrigin;
}

//@}---------------------------------------------------------------------

