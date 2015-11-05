/*
 * LPRay.h
 *
 *  Created on: 29 juin 2013
 *      Author: hallison
 */

#ifndef RAY_H_
#define RAY_H_

#include "Vector3.h"
#include "Displacement.h"

namespace LayerSceneGraph {
/**
 * Ray class. A ray is represented by a source point and a direction. A ray can be used for many auxiliary strategies inside a 3D world, such as 3D picking and ray tracing rendering methods
 */
class LPRay {
private:
	Vector3 source;
	Displacement direction;
public:
	LPRay(Vector3 s = Vector3(0,0,0), Vector3 dir = Vector3(0,0,1));
	virtual ~LPRay();

	LPRay& operator=(const LPRay& ray);
	Displacement getDirection();
	Vector3 getSourcePoint();
	Vector3 computePoint(float parameter);
};

} /* namespace LayerSceneGraph */
#endif /* RAY_H_ */
