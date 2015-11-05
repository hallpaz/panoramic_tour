/*
 * Vector4.cpp
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#include "Vector4.h"
#include "Vector3.h"

namespace LayerSceneGraph {

Vector4::Vector4() {
	x = 0;	y = 0; 	z = 0; w = 0;
}

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(const Vector4 &v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}

Vector4::~Vector4() {
	// TODO Auto-generated destructor stub
	//no memory to deallocate
}


Vector4 Vector4::operator +(const Vector4& v) {
	Vector4 result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	result.z = this->z + v.z;
	result.w = this->w + v.w;
	return result;
}


float Vector4::dot(Vector4 v) {
	return (x*v.x + y*v.y + z*v.z + w*v.w);
}

Vector4& Vector4::operator =(const Vector4& v) {
	if(this != &v){
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = v.w;
	}
	return *this;
}

void Vector4::setValues(float* values) {
	x = values[0];
	y = values[1];
	z = values[2];
	w = values[3];
}

float Vector4::operator [](int i) {
	switch(i){
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		return 0;
		//TODO throws exception
	}
}

} /* namespace LayerSceneGraph */
