/*
 * Vector4.h
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#ifndef VECTOR4_H_
#define VECTOR4_H_


namespace LayerSceneGraph {

class Vector4 {
private:
	float x, y, z, w;
	Vector4 operator+(const Vector4 &v);
	Vector4 operator-(const Vector4& v);
public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4& v);
	virtual ~Vector4();

	Vector4 inverse();

	float dot(Vector4 v);
	Vector4& operator=(const Vector4& v);

	float operator[](int i);

	void setValues(float *values);

};

} /* namespace LayerSceneGraph */
#endif /* VECTOR4_H_ */
