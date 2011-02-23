/*
 *  OrbitingCamera.cpp
 *  Earth
 *
 *  Created by Arman Uguray on 2/22/11.
 *  Copyright 2011 Brown University. All rights reserved.
 *
 */

#include "OrbitingCamera.h"

OrbitingCamera::OrbitingCamera() : Camera()
{
	
}

void OrbitingCamera::mouse_dragged(REAL x, REAL y)
{
	Vector4 e = ((m_projection * m_modelview).getInverse() * Vector4(-x,y,0.f,1.f)).getHomogenized();
	Vector4 axis = eye.cross(e);
	axis.w = 0;
	x *= 0.005;
	y *= 0.005;
	REAL angle = sqrt(x*x+y*y);
	e = getRotMat(Vector4(0,0,0,1), axis, angle) * eye;
	Vector3 ey(e.x,e.y,e.z);
	Vector3 upp(up.x,up.y,up.z);
	Vector3 lo(-e.x, -e.y, -e.z);
	lookAt(ey,lo,upp);
}
