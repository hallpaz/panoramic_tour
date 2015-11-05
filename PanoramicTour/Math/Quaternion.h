/*
 * Quaternion.h
 *
 *  Created on: 4 août 2013
 *      Author: hallison
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Matrix4.h"

namespace LayerSceneGraph {
/**
 * Missing implementation
 * */
class Quaternion {
private:
	float x, y, z, w;
public:
	Quaternion();
	virtual ~Quaternion();
	void operator=(Quaternion &rhs);
	Quaternion operator+(Quaternion &rhs);
	Quaternion operator-(Quaternion &rhs);
	Quaternion operator*(Quaternion &rhs);
	Quaternion conjugate();

	float lenght();
	void normalize();

	Matrix4 getRotationMatrix();
};

} /* namespace LayerSceneGraph */
#endif /* QUATERNION_H_ */
