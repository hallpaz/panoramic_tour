/*
 * Matrix4.cpp
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#include "Matrix4.h"
#include <math.h>

namespace LayerSceneGraph {

/**
 * Default constructor. Instances a identity matrix.
 */
Matrix4::Matrix4() {
	for(int i = 0; i< 16; i++){
		if((i%5) == 0){
			values[i] = 1.0;
		}
		else{
			values[i] = 0.0;
		}
	}
}
/**
 * Instances a matrix with values given by the parameter.
 */
Matrix4::Matrix4(float* v) {
	for(unsigned char i = 0; i < 16; i++){
		values[i] = v[i];
	}
}
/**
 * Copy constructor.
 */
Matrix4::Matrix4(const Matrix4& copy) {
	for(unsigned char i = 0; i < 16; i++){
		values[i] = copy.values[i];
	}
}
Matrix4::~Matrix4() {
	//no memory dynamically allocated
}
/**
 * Operator "=" overloading.
 */
Matrix4& Matrix4::operator =(const Matrix4& matrix) {
	if(this != &matrix){
		for(unsigned char i = 0; i < 16; i++){
			values[i] = matrix.values[i];
		}
	}
	return *this;
}
/**
 * Returns a float pointer with the 16 values of this matrix
 */
float* Matrix4::getValues() {
	return values;
}

void Matrix4::setValues(const float* v) {
	for(unsigned char i = 0; i < 16; i++){
		values[i] = v[i];
	}
}
/**
 * This method adds elements of this matrix with elements of another given matrix
 * in equivalent positions
 */
Matrix4 Matrix4::operator +(Matrix4 m) {
	float result[16];
	for(unsigned char i = 0; i < 16; i++){
		result[i] = this->values[i] + m.values[i];
	}
	return Matrix4(result);
}
/**
 * This method subtracts elements of this matrix with elements of another given matrix
 * in equivalent positions
 */
Matrix4 Matrix4::operator -(Matrix4 m) {
	return *this +( m * (-1));
}

/**
 * Canonical multiplication of matrices
 */
Matrix4 Matrix4::operator *(Matrix4 m) {
	float resultado[16];
	    // Fisrt Column
	resultado[0] = values[0]*m.values[0] + values[4]*m.values[1] + values[8]*m.values[2] + values[12]*m.values[3];
	resultado[1] = values[1]*m.values[0] + values[5]*m.values[1] + values[9]*m.values[2] + values[13]*m.values[3];
	resultado[2] = values[2]*m.values[0] + values[6]*m.values[1] + values[10]*m.values[2] + values[14]*m.values[3];
	resultado[3] = values[3]*m.values[0] + values[7]*m.values[1] + values[11]*m.values[2] + values[15]*m.values[3];

	// Second Column
	resultado[4] = values[0]*m.values[4] + values[4]*m.values[5] + values[8]*m.values[6] + values[12]*m.values[7];
	resultado[5] = values[1]*m.values[4] + values[5]*m.values[5] + values[9]*m.values[6] + values[13]*m.values[7];
	resultado[6] = values[2]*m.values[4] + values[6]*m.values[5] + values[10]*m.values[6] + values[14]*m.values[7];
	resultado[7] = values[3]*m.values[4] + values[7]*m.values[5] + values[11]*m.values[6] + values[15]*m.values[7];

	// Third Column
	resultado[8] = values[0]*m.values[8] + values[4]*m.values[9] + values[8]*m.values[10] + values[12]*m.values[11];
	resultado[9] = values[1]*m.values[8] + values[5]*m.values[9] + values[9]*m.values[10] + values[13]*m.values[11];
	resultado[10] = values[2]*m.values[8] + values[6]*m.values[9] + values[10]*m.values[10] + values[14]*m.values[11];
	resultado[11] = values[3]*m.values[8] + values[7]*m.values[9] + values[11]*m.values[10] + values[15]*m.values[11];

	// Fourth Column
	resultado[12] = values[0]*m.values[12] + values[4]*m.values[13] + values[8]*m.values[14] + values[12]*m.values[15];
	resultado[13] = values[1]*m.values[12] + values[5]*m.values[13] + values[9]*m.values[14] + values[13]*m.values[15];
	resultado[14] = values[2]*m.values[12] + values[6]*m.values[13] + values[10]*m.values[14] + values[14]*m.values[15];
	resultado[15] = values[3]*m.values[12] + values[7]*m.values[13] + values[11]*m.values[14] + values[15]*m.values[15];

	return Matrix4(resultado);
}
/**
 * This method multiplies this matrix for a given float number.
 * Each value in the matrix is multiplied by the float number.
 */
Matrix4 Matrix4::operator *(float n) {
	float result[16];
	for(unsigned char i = 0; i < 16; i++){
		result[i] = values[i]*n;
	}
	return Matrix4(result);
}

/**
 * Returns the value in "i" position inside the matrix. The matrix is column packed
 * so Matrix[5] is equivalent to matrix[1][0].
 */
float Matrix4::operator [](int i) const{
	return values[i];
}
    
float &Matrix4::operator[](int i){
    return values[i];
}

/**
 * This method multiplies this matrix by a rotation matrix which rotates it around the X axis by a
 * given angle
 */
Matrix4 Matrix4::rotationAroundX(float angle){
	Matrix4 m;
	angle = toRadian(angle);
	m.values[5] = cosf(angle);
	m.values[6] = sinf(angle);
	m.values[9] = -sinf(angle);
	m.values[10] = cosf(angle);

	return m;
}
/**
 * This method multiplies this matrix by a rotation matrix which rotates it around the Y axis by a
 * given angle
 */
Matrix4 Matrix4::rotationAroundY(float angle){
    // Rotate Y formula.
	Matrix4 m;
	angle = toRadian(angle);
    m.values[0] = cosf(angle);
    m.values[2] = -sinf(angle);
    m.values[8] = -m.values[2];
    m.values[10] = m.values[0];

    return m;
}
/**
 * This method multiplies this matrix by a rotation matrix which rotates it around the Z axis by a
 * given angle
 */
Matrix4 Matrix4::rotationAroundZ(float angle){
    // Rotate Z formula.
	Matrix4 m;
	angle = toRadian(angle);
    m.values[0] = cosf(angle);
    m.values[1] = sinf(angle);
    m.values[4] = -m.values[1];
    m.values[5] = m.values[0];

    return m;
}

/**
 * Returns a matrix 4x4 which represents a rotation transform based on values
 * to the Euler angles Alpha, Beta and Gamma
 */
Matrix4 Matrix4::rotation(float alpha, float beta, float gamma) {
    //TODO: CHECK THE ORDER. MAYBE THEY ARE DIFFERENT FOR OBJECTS AND FOR CAMERAS
	Matrix4 rotationMatrix = rotationAroundX(alpha)*rotationAroundY(beta)*rotationAroundZ(gamma);

	return rotationMatrix;
}

Matrix4 Matrix4::scale(float sx, float sy, float sz) {
	Matrix4 scaleMatrix;

	scaleMatrix.values[0] = sx;
	scaleMatrix.values[5] = sy;
	scaleMatrix.values[10] = sz;

	return scaleMatrix;
}
/**
 * Returns a matrix 4x4 which represents a translation transform
 * based on values to X, Y and Z directions
 * @todo implement this method
 */
Matrix4 Matrix4::translation(float x, float y, float z) {
	Matrix4 translationMatrix;
	translationMatrix.values[12] = x;
	translationMatrix.values[13] = y;
	translationMatrix.values[14] = z;
	return translationMatrix;
}

Matrix4 Matrix4::transpose() {
	Matrix4 transpost;
	for(unsigned char i = 0; i < 4; i++){
		for(unsigned char j = 0; j < 4; j++){
			transpost.values[j*4 + i] = values[i*4 + j];
		}
	}
	return transpost;
}

Matrix4 Matrix4::transposeRotation(){
	Matrix4 transpost;
	for(unsigned char i = 0; i < 4; i++){
		for(unsigned char j = 0; j < 4; j++){
			if(j == 3 || i == 3){
				transpost.values[j*4 + i] = values[j*4 + i];
			}else{
				transpost.values[j*4 + i] = values[i*4 + j];
			}
		}
	}
	return transpost;
}


//TODO implement it!
/**
 * Algorithm to invert a 4 x 4 matrix based on Gauss elimination
 */
Matrix4 Matrix4::inverse() {
	Matrix4 inverse;
//	Matrix4 copy(*this);
//	float determinat = 1;
//	float p, c;
//	GLuint l;
//	for(int i = 0; i < 4; i++){
//		c = values[5*i];
//		for(unsigned char k = i; k < 4; k++){
//			if(fabs(c) < fabs(values[i*4 + k])){
//				c = values[i*4 + k];
//				l = k;
//			}
//		}
//		if(l != i){
//			for(unsigned char j = 0; j < 4; j++){
//				c = copy[j*4 + i];
//				copy.values[j*4 + i] = copy.values[j*4 + l];
//				copy.values[j*4+l] = c;
//
//				c = inverse[j*4 + i];
//				inverse.values[j*4 + i] = inverse.values[j*4 + l];
//				inverse.values[j*4+l] = c;
//			}
//		}
//		p = values[5*i];
//		//determinat = determinat*p;
//		if(p){
//			for(unsigned char j =0; j < 4; j++){
//				copy.values[4*j + i] = copy.values[4*j +i]/p;
//				inverse.values[4*j + i] = inverse.values[4*j + i]/p;
//			}
//			for(unsigned char k = 0; k < 4; k++){
//				if(k != i){
//					p = copy[i*4 + k];
//					for(unsigned char j = i; j < 4; j++){
//						copy.values[j*4 + k] = (copy[j*4+k] - p*copy[j*4 + i]);
//						inverse.values[j*4 + k] = (inverse[j*4+k] - p*inverse[j*4 + i]);
//					}
//				}
//			}
//		}
//	}
	return inverse;
}
/**
 * This method multiplies this matrix by a given fourth-dimensional vector,
 * returning a Vector4 as result.
 */
Vector4 Matrix4::operator *(Vector4 v) {
	float x, y, z, w;
	x = values[0]*v[0] + values[4]*v[1] + values[8]*v[2]+ values[12]*v[3];
	y = values[1]*v[0] + values[5]*v[1] + values[9]*v[2]+ values[13]*v[3];
	z = values[2]*v[0] + values[6]*v[1] + values[10]*v[2]+ values[14]*v[3];
	w = values[3]*v[0] + values[7]*v[1] + values[11]*v[2]+ values[15]*v[3];
	x = x/w; y = y/w; z = z/w; w = 1.0;

	return Vector4(x, y, z, w);
}
/**
 * This method multiplies this matrix by a given tridimensional vector,
 * returning a Vector3 as result.
 */
Vector3 Matrix4::operator *(Vector3 v) {
	Vector4 aux(v[0], v[1], v[2], 1.0);
	aux = (*this)*(aux);
	return Vector3(aux[0], aux[1], aux[2]);
}
/**
 * This method transforms a ray by this matrix and returns the ray transformed.
 * Transformation of a ray is defined by multiplication of the ray's source point
 * and the ray's direction (both Vector3 elements) by the same matrix
 */
LPRay Matrix4::operator *(LPRay& ray){
	Vector3 source = this->operator *(ray.getSourcePoint());
	Vector3 direction = this->operator *(ray.getDirection());
	return LPRay(source, direction);
}

Displacement Matrix4::operator *(Displacement d) {
	float x, y, z;
	x = values[0]*d[0] + values[4]*d[1] + values[8]*d[2];
	y = values[1]*d[0] + values[5]*d[1] + values[9]*d[2];
	z = values[2]*d[0] + values[6]*d[1] + values[10]*d[2];
	return Displacement(x, y, z);
}

/**
 * Converts a angle given in degrees to radians unit
 */
float Matrix4::toRadian(float angle) {
	return angle*M_PI/180.0;
}

} /* namespace LayerSceneGraph */
