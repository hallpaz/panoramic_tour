/*
 * Vector3.h
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "iostream"

#define INVALID_REQUEST 777

namespace LayerSceneGraph {

class Vector3 {
    friend class LPCamera;
protected:
	float x, y, z;

public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3 &v);

	virtual ~Vector3();
	Vector3 inverse();

	Vector3& operator=(const Vector3& v);
	Vector3 operator+(Vector3 v);
	Vector3 operator-(Vector3 v);
	Vector3 operator*(float scalar);
	Vector3 operator*(Vector3 crossed);
	Vector3 operator-();
	float dot(Vector3 v);
	float operator[](int i) const;
    float& operator[](int i);

	void normalize();
	float lenght();
	Vector3 getProjectionOnPlane(Vector3 normal);

	void setValues(float x, float y, float z);
	void setValues(float *values);
    
    friend std::ostream& operator<< (std::ostream& stream, const Vector3& vector);

};
Vector3 operator*(float scalar, Vector3& v);

} /* namespace LayerSceneGraph */
#endif /* VECTOR3_H_ */
