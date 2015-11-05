/*
 * LPRay.cpp
 *
 *  Created on: 29 juin 2013
 *      Author: hallison
 */

#include "LPRay.h"

namespace LayerSceneGraph {
/**
 * Constructor. A ray is initialized with a source vector and a direction vector
 */
LPRay::LPRay(Vector3 s, Vector3 dir) {
	source = s;
	direction = (Displacement&) dir;
}

/**
 * Destructor. Nothing to do.
 */
LPRay::~LPRay() {
	// TODO no memory to release
}

/**
 * Returns the direction vector of this ray
 * @return direction The direction of this ray
 */
Displacement LPRay::getDirection() {
	return direction;
}
/**
 * Operator "=" overload. Assigns source and direction vectors
 */
LPRay& LPRay::operator =(const LPRay& ray) {
	if(this != &ray){
		source = ray.source;
		direction = ray.direction;
	}
	return *this;
}

/**
 * Returns a vector which represents the origin of this ray
 * @return source A Vector3 that represents the source point of this ray
 */
Vector3 LPRay::getSourcePoint() {
	return source;
}
/**
 * Computes a 3 dimensional point in this ray's direction based on a parameter
 * @param parameter The input parameter to compute the point
 * @return The corresponding point to the give parameter
 */
Vector3 LPRay::computePoint(float parameter) {
	return(source + parameter*direction);
}

} /* namespace LayerSceneGraph */
