/*
 * Vector3.cpp
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#include <math.h>

#include "Vector3.h"

namespace LayerSceneGraph {

Vector3::Vector3() {
	x = 0;	y = 0; 	z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3 &v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vector3::~Vector3() {
	// TODO Auto-generated destructor stub
}

Vector3 Vector3::inverse() { //avoid using for while
	Vector3 v(-x, -y, -z);
	return v;
}

Vector3 Vector3::operator +(Vector3 v) {
	Vector3 result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	result.z = this->z + v.z;
	return result;
}

Vector3 Vector3::operator -(Vector3 v) {
	Vector3 result;
	result.x = this->x - v.x;
	result.y = this->y - v.y;
	result.z = this->z - v.z;
	return result;
}

Vector3 Vector3::operator *(float scalar) {
	Vector3 v(scalar*this->x, scalar*this->y, scalar*this->z);
	return v;
}

Vector3 Vector3::operator *(Vector3 v) {
	Vector3 *result;
	float tempX = y * v.z - z * v.y;
	float tempY = z * v.x - x * v.z;
	float tempZ = x * v.y - y * v.x;
	result = new Vector3(tempX, tempY, tempZ);
	return *result;
}

inline float Vector3::lenght(){
	return sqrt(x*x + y*y + z*z);
}

void Vector3::normalize() {
	x = x/lenght();
	y = y/lenght();
	z = z/lenght();
}

void Vector3::setValues(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::dot(Vector3 v) {
	return (x*v.x + y*v.y + z*v.z);
}

Vector3& Vector3::operator =(const Vector3& v) {
	if(this != &v){
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}
	return *this;
}

Vector3 Vector3::getProjectionOnPlane(Vector3 normal) {
	return Vector3 (*this - normal*(this->dot(normal)));
}

void Vector3::setValues(float* values) {
	this->setValues(values[0], values[1], values[2]);
}

float Vector3::operator [](int i) const{
	switch(i){
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		return INVALID_REQUEST;
	}
}

float& Vector3::operator[](int i){
    switch(i){
        case 0:
            return x;
        case 1:
            return y;
        default:
            return z;
    }
}

Vector3 operator *(float scalar, Vector3& v) {
	return (v*scalar);
}
    
    std::ostream& operator<< (std::ostream& stream, const Vector3& vector){
        stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return stream;
    }
} /* namespace LayerSceneGraph */


