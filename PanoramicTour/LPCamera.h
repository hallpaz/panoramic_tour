/*
 * LPCamera.h
 *
 *  Created on: 26 juin 2013
 *      Author: hallison
 */

#ifndef CAMERA_H_
#define CAMERA_H_


#include "Matrix4.h"
#include "Vector3.h"

namespace LayerSceneGraph {
/**
 * Camera class: Responsible for encapsulate all matrix operations for visualization
 */
class LPCamera {
private:
	Matrix4 modelMatrix;
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;
	Matrix4 correctionMatrix;

	float near;
	float far;
	float angleOfView;
	uint width;
	uint height;

	Vector3 position;
public:
	LPCamera(float near = 0.1, float far = 50, float angleOfView = 60, uint width = 360,
             uint height = 480, Matrix4 correctionMatrix = Matrix4::rotationAroundX(90) );
	virtual ~LPCamera();

	void buildPerspective(uint width, uint height, float angleOfView);

	Matrix4 getModelMatrix();
	Matrix4 getViewMatrix();
	Matrix4 getProjectionMatrix();
	const float *getModelViewMatrix();

	void setModelMatrix(const float *matrix);
	void setViewMatrix(const float *matrix);
	void setProjectionMatrix(const float *matrix);
    void setPosition(float x, float y, float z);

	void setModelMatrix(const Matrix4& matrix);
	void setViewMatrix(Matrix4& matrix);
	void setProjectionMatrix(const Matrix4& matrix);

	uint getWidth();
	uint getHeight();
	float getAngleOfView();
	float getAspectRatio();
	float getNearDistance();
	float getFarDistance();

	Vector3 getHorizontalDirection();
	Vector3 getLookDirection();
	Vector3 getUpDirection();
	Vector3 getPosition();

};

} /* namespace LayerSceneGraph */
#endif /* CAMERA_H_ */
