/*
 * Displacement.h
 *
 *  Created on: 28 juil. 2013
 *      Author: hallison
 */

#ifndef DISPLACEMENT_H_
#define DISPLACEMENT_H_

/**
 * This class represents directions, 3D vectors that can be rotated, scaled but should not be
 * translated. It is very useful to represent normal vectors and the direction vector of a ray
 */
class Displacement {
public:
	Displacement();
	Displacement(float x, float y, float z);
	virtual ~Displacement();
};

#endif /* DISPLACEMENT_H_ */
