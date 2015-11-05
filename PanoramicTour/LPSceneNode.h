/*
 * LPSceneNode.h
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#ifndef LPSCENENODE_H_
#define LPSCENENODE_H_

#include <vector>

#include "Matrix4.h"
#include "Vector3.h"
#include <cstdlib>


namespace LayerSceneGraph {

class LPSceneNode {
private:
    std::string identifier;
protected:
	Matrix4 transform;
	Matrix4 worldTransform;
	//Inverse world transformation is necessary for some computations.
	Matrix4 inverseWorldTransform;
	Matrix4 inverseTransform;

	LPSceneNode *parent;

    std::vector<LPSceneNode*> children;

	Vector3 position;

public:
	LPSceneNode();
	virtual ~LPSceneNode();
	virtual void draw();
	virtual void update(float clockTick);
	void addChild(LPSceneNode *s);
	LPSceneNode *removeChild();

	Matrix4 getTransform();
	void setTransform(Matrix4 m, Matrix4 i);
	Matrix4 getWorldTransform();
	void setWorldTransform(Matrix4 m);

	Matrix4 getInverseTransform();
	Matrix4 getWorldInverseTransform();

	Vector3 getPosition();
	void setPosition(Vector3 pos);
	void setPosition(float x, float y, float z);
	void translateBy(float x, float y, float z);

	void scaleBy(float scaleFactor);
	void scaleBy(float sX, float sY, float sZ);
	void scaleX(float sX);
	void scaleY(float sY);
	void scaleZ(float sZ);

	void rotateBy(float alpha, float beta, float gamma);
	void rotateAroundX(float rX);
	void rotateAroundY(float ry);
	void rotateAroundZ(float rz);

	LPSceneNode *getParent();

    LPSceneNode* getChildByIdentifier(std::string _identifier);
    void setIdentifier(std::string _id);
    std::string getIdentifier();
    std::vector <LPSceneNode*>::const_iterator getChildteratorStart();
    std::vector <LPSceneNode*>::const_iterator getChildteratorEnd();
};

} /* namespace LayerSceneGraph */
#endif /* LPSCENENODE_H_ */
