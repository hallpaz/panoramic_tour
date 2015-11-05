/*
 * Matrix4.h
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#ifndef MATRIX4_H_
#define MATRIX4_H_

#include "Vector4.h"
#include "Vector3.h"
#include "Displacement.h"
#include "LPRay.h"

namespace LayerSceneGraph {
/**
 * A matrix 4x4
 * @todo implement a operator[][] for matrix access
 */
class Matrix4 {
private:
	float values[16];
	void pivoteamento(uint i);
public:
	Matrix4();
	Matrix4(float *v);
	Matrix4(const Matrix4& copy);
	virtual ~Matrix4();

	float *getValues();
	void setValues(const float *v);

	Matrix4& operator=(const Matrix4& matrix);
	static Matrix4 scale(float x, float y, float z);
	static Matrix4 translation(float x, float y, float z);
	static Matrix4 rotationAroundX(float angle);
	static Matrix4 rotationAroundY(float angle);
	static Matrix4 rotationAroundZ(float angle);
	static Matrix4 rotation(float alpha, float beta, float gamma);

	//Operations
	Matrix4 operator+(Matrix4 m);
	Matrix4 operator-(Matrix4 m);
	Matrix4 operator*(Matrix4 m);
	Vector4 operator*(Vector4 v);
	Vector3 operator*(Vector3 v);
	Displacement operator*(Displacement d);
	Matrix4 operator*(float n);
	LPRay 	operator*(LPRay& ray);

    float operator[](int i) const;
    float & operator[](int i);
	Matrix4 transpose();
	Matrix4 transposeRotation();
	Matrix4 inverse();

	static float toRadian(float angle);
};

} /* namespace LayerSceneGraph */
#endif /* MATRIX4_H_ */
