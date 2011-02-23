/*
 *  OrbitingCamera.h
 *  Earth
 *
 *  Created by Arman Uguray on 2/22/11.
 *  Copyright 2011 Brown University. All rights reserved.
 *
 */

#ifndef ORBITINGCAMERA_H
#define ORBITINGCAMERA_H

#include "Camera.h"

class OrbitingCamera : public Camera {
public:
	OrbitingCamera();
	
	void mouse_dragged(REAL x, REAL y);
};


#endif // ORIBITINGCAMERA_H