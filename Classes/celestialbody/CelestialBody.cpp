/*
 *  CelestialBody.cpp
 *  Earth
 *
 *  Created by Arman Uguray on 2/24/11.
 *  Copyright 2011 Brown University. All rights reserved.
 *
 */

#include "CelestialBody.h"

CelestialBody::CelestialBody()
{
	m_program = 0;
	m_ctm = Matrix4x4::identity();
}

CelestialBody::~CelestialBody()
{
	if (m_program) {
		glDeleteProgram(m_program);
	}
}