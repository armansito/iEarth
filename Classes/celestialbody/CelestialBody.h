/*
 *  CelestialBody.h
 *  Earth
 *
 *  Created by Arman Uguray on 2/24/11.
 *  Copyright 2011 Brown University. All rights reserved.
 *
 */

#ifndef CELESTIALBODY_H_
#define CELESTIALBODY_H_

#import <OpenGLES/ES2/gl.h>
#include "CS123Algebra.h"

class CelestialBody 
{	
public:
	CelestialBody();
	virtual ~CelestialBody();
	virtual void draw(GLfloat projectionMatrix[16], GLfloat modelviewMatrix[16]) = 0;
	
protected:
	GLuint m_program;
	Matrix4x4 m_ctm;
};

#endif // CELESTIALBODY_H_