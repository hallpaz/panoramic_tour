/*
 * LPCamera.cpp
 *
 *  Created on: 26 juin 2013
 *      Author: hallison
 */

#include <math.h>

#include "LPCamera.h"

namespace LayerSceneGraph {

/**
 * Default constructor. Initialize camera parameters with default values.
 * Default values: near = 0.001; far = 50.0;
 * width = 360; height = 480; angleOfView = 45;
 *@todo add parameters default
 */
LPCamera::LPCamera(float near, float far, float angleOfView, uint width,
		uint height, Matrix4 correctionMatrix) {
	this->near = near;
	this->far = far;
	this->width = width;
	this->height = height;
	this->angleOfView = angleOfView;
	this->correctionMatrix = correctionMatrix;
}

/**
 * Destructor. There isn't any dynamic allocated memory for any object.
 */
LPCamera::~LPCamera() {
	//nothing to do
}

/**
 * Returns the model matrix (a pointer with 16 float values).
 */
Matrix4 LPCamera::getModelMatrix() {
	return modelMatrix;
}

/**
 * Returns the view matrix (a pointer with 16 float values).
 */
Matrix4 LPCamera::getViewMatrix() {
	return viewMatrix;
}

/**
 * Returns the projection matrix (a pointer with 16 float values).
 */
Matrix4 LPCamera::getProjectionMatrix() {
	return projectionMatrix;
}

/**
 * Receives a pointer with 16 float values and sets a new model matrix.
 */
void LPCamera::setModelMatrix(const float* matrixValues) {
	modelMatrix.setValues(matrixValues);
}

/**
 * Receives a pointer with 16 float values and sets a new view matrix.
 */
void LPCamera::setViewMatrix(const float* matrixValues) {
	viewMatrix.setValues(matrixValues);
	viewMatrix = viewMatrix*correctionMatrix;
}

/**
 * Receives a pointer with 16 float values and sets a new projection matrix.
 */
void LPCamera::setProjectionMatrix(const float* matrixValues) {
	projectionMatrix.setValues(matrixValues);
}
/**
 * Receives a matrix4 a sets a new model matrix
 */
void LPCamera::setModelMatrix(const Matrix4& matrix) {
	modelMatrix = matrix;
}
/**
 * Receives a matrix4 a sets a new view matrix
 */
void LPCamera::setViewMatrix(Matrix4& matrix) {
	viewMatrix = matrix*correctionMatrix;
}
/**
 * Receives a matrix4 a sets a new projection matrix
 */
void LPCamera::setProjectionMatrix(const Matrix4& matrix) {
	projectionMatrix = matrix;
}
    
void LPCamera::setPosition(float incx, float incy, float incz){
    position.setValues(incx, incy, incz);
    position.x += incx;
    position.y += incy;
    position.z += incz;
    
    viewMatrix = (Matrix4::translation(incx, incy, incz)*viewMatrix);
}

/**
 * Pre-multiplies the view and model matrix and then returns the result
 * @todo maybe i can remove this method later
 */
const float* LPCamera::getModelViewMatrix() {
	return ((viewMatrix)*(modelMatrix)).getValues();
}

/**
 * Computes and build a new perspective matrix based on the width, height and angleOfView parameters
 */
void LPCamera::buildPerspective(uint width, uint height, float angleOfView) {
		float matriz[16];
		this->width = width; this->height = height;
		this->angleOfView = angleOfView;
		float aspectRatio = (float) width/height;

		// Some calculus before the formula.
		float size = near * tanf(angleOfView*M_PI / 360.0);
		float left = -size, right = size;
		float	bottom = -size / aspectRatio, top = size / aspectRatio;

		// First Column
		matriz[0] = 2 * near / (right - left);
		matriz[1] = 0.0;
		matriz[2] = 0.0;
		matriz[3] = 0.0;

		// Second Column
		matriz[4] = 0.0;
		matriz[5] = 2 * near / (top - bottom);
		matriz[6] = 0.0;
		matriz[7] = 0.0;

		// Third Column
		matriz[8] = (right + left) / (right - left);
		matriz[9] = (top + bottom) / (top - bottom);
		matriz[10] = -(far + near) / (far - near);
		matriz[11] = -1;

		// Fourth Column
		matriz[12] = 0.0;
		matriz[13] = 0.0;
		matriz[14] = -(2 * far * near)/(far - near);
		matriz[15] = 0.0;

		projectionMatrix.setValues(matriz);
}

/**
 * Returns the width of the screen (device coordinates)
 */
uint LPCamera::getWidth() {
	return width;
}

/**
 * Returns the height of the screen (device coordinates)
 */
uint LPCamera::getHeight() {
	return height;
}

/**
 * Returns the aspect ratio value of the screen (device coordinates)
 */
float LPCamera::getAspectRatio() {
	return (float) width/height;
}
/**
 * Returns a vector which represents the horizontal direction in camera's coordinate system.
 */
Vector3 LPCamera::getHorizontalDirection() {
	return Vector3(viewMatrix[0], viewMatrix[4], viewMatrix[8]);
}
/**
 * Returns a vector which represents the upper direction.
 */
Vector3 LPCamera::getUpDirection() {
	return Vector3 (viewMatrix[1], viewMatrix[5], viewMatrix[9]);
}
/**
 * Returns a vector which represents the direction to where camera is pointing
 * Attention to vector inversion
 */
Vector3 LPCamera::getLookDirection() {
	return Vector3 (-viewMatrix[2], -viewMatrix[6], -viewMatrix[10]);
}

/**
 * Returns the value specified for the angle of view
 */
float LPCamera::getAngleOfView() {
	return angleOfView;
}

/**
 * Returns the distance to the near plane. All objects localized before the near plane are not visible.
 */
float LPCamera::getNearDistance() {
	return near;
}
/**
 * Returns the distance to the far plane. All objects localized after the far plane are not visible.
 */
float LPCamera::getFarDistance() {
	return far;
}

/**
 * Returns a vector which represents camera's position inside the scene
 */
Vector3 LPCamera::getPosition(){
	return position;
}

} /* namespace LayerSceneGraph */
