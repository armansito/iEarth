/*
 *  Camera.cpp
 *  Earth
 *
 *  Created by Arman Uguray on 2/22/11.
 *  Copyright 2011 Brown University. All rights reserved.
 *
 */

#include "Camera.h"

Camera::Camera()
{
	aspect_ratio = 320.f/480.f;
	height = 45.f;
	near = 0.1f;
	far = 30000.f;
	Vector3 eye(3,0,3);
	Vector3 look(-1,0,-1);
	Vector3 up(0,1,0);
	lookAt(eye,look,up);
}

void Camera::setSize(REAL w, REAL h)
{
	aspect_ratio = w/h;
	loadMatrices();
}

Matrix4x4 Camera::getProjectionMatrix() const
{
	return m_projection;
}
Matrix4x4 Camera::getModelviewMatrix() const
{
	return m_modelview;
}

void Camera::setFOV(REAL h)
{
	height = h/2.f;
	loadMatrices();
}

void Camera::setClip(REAL nearPlane, REAL farPlane)
{
	near = nearPlane;
	far = farPlane;
	loadMatrices();
}

void Camera::lookAt(const Vector3 &e, const Vector3 &l, const Vector3 &upp)
{
	this->eye = Vector4(e.x, e.y, e.z, 1.0f);
	this->look = Vector4(l.x, l.y, l.z, 0.0f);
	this->up = Vector4(upp.x, upp.y, upp.z, 0.0);
	this->w = (-look).getNormalized();
	this->v = (up - w.dot(up)*w).getNormalized();
	this->u = v.cross(w).getNormalized();
	loadMatrices();
}

void Camera::lookVectorTranslate(REAL delta)
{
    eye += w * (delta * -0.005);
	loadMatrices();
}

void Camera::loadMatrices()
{
	REAL height_2 = tan(M_PI*height/360.f)*far;
    REAL width_2 = aspect_ratio * height_2;
    REAL x = 1.f/(width_2);
    REAL y = 1.f/(height_2);
    REAL z = 1.f/far;
    REAL c = -near/far;
	Matrix4x4 m3 = Matrix4x4(x, 0 , 0 , 0,
                             0, y , 0 , 0,
                             0, 0 , z , 0,
                             0, 0 , 0 , 1);
    Matrix4x4 m2 = Matrix4x4(1, 0 ,   0   ,  0  ,
                             0, 1 ,   0   ,  0  ,
                             0, 0,-1/(c+1),c/(c+1),
                             0, 0 ,  -1   ,  0  );
    m_projection = m2 * m3;
	Matrix4x4 m5 = Matrix4x4(1, 0, 0, -eye.x,
							 0, 1, 0, -eye.y,
							 0, 0, 1, -eye.z,
							 0, 0, 0,    1  );
    Matrix4x4 m4 = Matrix4x4(u.x, u.y, u.z, 0,
                             v.x, v.y, v.z, 0,
                             w.x, w.y, w.z, 0,
							 0 ,  0 ,  0 , 1);
	m_modelview = m4 * m5;
}

