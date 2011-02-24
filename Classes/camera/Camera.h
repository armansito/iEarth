/*
 *  Camera.h
 *  Earth
 *
 *  Created by Arman Uguray on 2/22/11.
 *  Copyright 2011 Brown University. All rights reserved.
 *
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "CS123Algebra.h"

class Camera {
public:
	Camera();
	
	Matrix4x4 getProjectionMatrix() const;
	Matrix4x4 getModelviewMatrix() const;
	inline Vector4 getEye() const { return eye; }
	void lookAt(const Vector3 &eye, const Vector3 &look, const Vector3 &up);
	void setFOV(REAL h);
	void setClip(REAL nearPlane, REAL farPlane);
	void setSize(REAL width, REAL height);
	
	void lookVectorTranslate(REAL delta);
	
protected:
	
	void loadMatrices();
	
	Matrix4x4 m_projection, m_modelview;
	Vector4 eye, up, look, u, v, w;
	REAL near, far, aspect_ratio, height;
	
};

#endif // CAMERA_H