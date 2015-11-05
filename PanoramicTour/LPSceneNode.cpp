/*
 * LPSceneNode.cpp
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#include "LPSceneNode.h"

using namespace std;

namespace LayerSceneGraph {

/**
 * Dafault constructor. Instances  a transform and a world transform matrix and
 * set its parent as NULL.
 */
LPSceneNode::LPSceneNode() {
	parent = NULL;
}

/**
 * Destructor. Releases and deletes all children of this node.
 */
LPSceneNode::~LPSceneNode() {
	for(unsigned int i = 0; i < children.size (); ++ i) {
		delete children [ i ];
	}
}

/**
 * Adds another node as a child of this node.
 * @param s The node to be inserted
 */
void LPSceneNode::addChild(LPSceneNode *s) {
	s->parent = this;
	children.push_back(s);
}

/**
 * Removes the last child added from this node children vector.
 */
LPSceneNode *LPSceneNode::removeChild(){
	LPSceneNode *s = children.back();
	s->parent = NULL;
	children.pop_back();
	return s;
}

/**
 * Returns the local transformation matrix of this node
 * @return transform The local transforma
 */
Matrix4 LPSceneNode::getTransform() {
	return transform;
}

/**
 * Sets a new transform matrix for this node.
 * @param m,i The 4x4 matrix transform and its inverse
 */
void LPSceneNode::setTransform(Matrix4 m, Matrix4 i) {
	transform = m;
	inverseTransform = i;
}

/**
 * Returns the world transform matrix of this node. This matrix represents the transformation
 * of this node relative to the complete scene.
 * @return worldTransform The 4x4 matrix which
 */
Matrix4 LPSceneNode::getWorldTransform() {
	return worldTransform;
}
/**
 * Sets a new world transform for this node.
 * @param Matrix4 m A 4x4 matrix
 */
void LPSceneNode::setWorldTransform(Matrix4 m) {
	worldTransform = m;
}


/**
 * Return this node's parent.
 * @result parent This node's parent
 */
LPSceneNode* LPSceneNode::getParent() {
	return parent;
}
/**
 * Returns this node position in its local coordinate system.
 * @result position A 3 dimensional vector with node's position coordinates
 */
Vector3 LPSceneNode::getPosition() {
	return position;
}

/**
 * Sets this node position equal to given vector values
 */
void LPSceneNode::setPosition(Vector3 pos) {
	position = pos;
    transform[12] = pos[0];
    transform[13] = pos[1];
    transform[14] = pos[2];
	inverseTransform[12] = -pos[0];
    inverseTransform[13] = -pos[1];
    inverseTransform[14] = -pos[2];

    //transform = Matrix4::translation(position[0], position[1], position[2]);
	//TODO implement this correctly, must change only position
}
/**
 * Sets this node position coordinates given by x, y, z
 */
void LPSceneNode::setPosition(float x, float y, float z) {
	position.setValues(x, y, z);
    transform[12] = x;
    transform[13] = y;
    transform[14] = z;
    inverseTransform[12] = -x;
    inverseTransform[13] = -y;
    inverseTransform[14] = -z;
}
/**
 * Translate this node position by values specified
 */
void LPSceneNode::translateBy(float x, float y, float z) {
	position = position + Vector3(x, y, z);
	transform = Matrix4::translation(x, y, z)* transform;
	inverseTransform = inverseTransform*Matrix4::translation(-x, -y, -z);
}
/**
 * Scale this node uniformly
 */
void LPSceneNode::scaleBy(float scaleFactor) {
	transform = Matrix4::scale(scaleFactor, scaleFactor, scaleFactor) * transform;
	inverseTransform = inverseTransform*Matrix4::scale(1/scaleFactor, 1/scaleFactor, 1/scaleFactor);
}

void LPSceneNode::scaleBy(float sX, float sY, float sZ) {
	transform = Matrix4::scale(sX, sY, sZ) * transform;
	inverseTransform = inverseTransform*Matrix4::scale(1/sX, 1/sY, 1/sZ);
}

void LPSceneNode::scaleX(float sX) {
	transform = Matrix4::scale(sX, 0, 0) * transform;
	inverseTransform = inverseTransform*Matrix4::scale(1/sX, 1, 1);
}

void LPSceneNode::scaleY(float sY) {
	transform = Matrix4::scale(0, sY, 0) * transform;
	inverseTransform = inverseTransform*Matrix4::scale(1, 1/sY, 1);
}

void LPSceneNode::scaleZ(float sZ) {
	transform = Matrix4::scale(0, 0, sZ) * transform;
	inverseTransform = inverseTransform*Matrix4::scale(1, 1, 1/sZ);
}
/**
 * Makes a free rotation in this node, specifying euler angles
 */
void LPSceneNode::rotateBy(float alpha, float beta, float gamma) {
	transform = Matrix4::rotation(alpha, beta, gamma)*transform;
	inverseTransform = inverseTransform*Matrix4::rotation(alpha, beta, gamma);
}
/**
 * Rotates node around X axis by an angle
 */
void LPSceneNode::rotateAroundX(float rX) {
	transform = Matrix4::rotationAroundX(rX) * transform;
	inverseTransform = inverseTransform*Matrix4::rotationAroundX(-rX);
}
/**
 * Rotates node around Y axis by an angle
 */
void LPSceneNode::rotateAroundY(float rY) {
	transform = Matrix4::rotationAroundY(rY) * transform;
	inverseTransform = inverseTransform*Matrix4::rotationAroundY(-rY);
}
/**
 * Rotates node around Z axis by an angle
 */
void LPSceneNode::rotateAroundZ(float rZ) {
	transform = Matrix4::rotationAroundZ(rZ) * transform;
	inverseTransform = inverseTransform*Matrix4::rotationAroundZ(-rZ);
}

vector <LPSceneNode*>::const_iterator LPSceneNode::getChildteratorStart(){
		return children.begin();
}

Matrix4 LPSceneNode::getInverseTransform() {
	return inverseTransform;
}

Matrix4 LPSceneNode::getWorldInverseTransform() {
	return inverseWorldTransform;
}

void LPSceneNode::update(float clockTick) {
	if(parent){
		worldTransform = (parent->getWorldTransform())*transform;
		inverseWorldTransform = inverseTransform*parent->getWorldInverseTransform();
	}
	else{
		worldTransform = transform;
		inverseWorldTransform = inverseTransform;
	}
    vector<LPSceneNode*>::const_iterator nodeIterator;
    for(nodeIterator = getChildteratorStart(); nodeIterator != getChildteratorEnd(); ++nodeIterator)
    {
        (*nodeIterator)->update(clockTick);
    }
}
void LPSceneNode::draw(){
    vector<LPSceneNode*>::const_iterator nodeIterator;
    for(nodeIterator = getChildteratorStart(); nodeIterator != getChildteratorEnd(); ++nodeIterator)
    {
        (*nodeIterator)->draw();
    }
}

vector<LPSceneNode*>::const_iterator LPSceneNode::getChildteratorEnd() {
		return children.end();
}
    
LPSceneNode* LPSceneNode::getChildByIdentifier(string _identifier)
{
    LPSceneNode *searchedNode = nullptr;
    vector<LPSceneNode*>::const_iterator iterator;
    for (iterator = getChildteratorStart(); iterator != getChildteratorEnd(); ++iterator) {
        LPSceneNode *node = *iterator;
        if(_identifier.compare(node->getIdentifier() ) == 0 )
            return node;
        else
            searchedNode = node->getChildByIdentifier(_identifier);
    }
    return searchedNode;
}

/**
 * Sets this node's string identifier
 * @param _id The new identifier for the node
 */
void LPSceneNode::setIdentifier(string _id){
    identifier = _id;
}
/**
 * Returns this node's string identifier
 * @return identifier A copy of identifier attribute
 */
string LPSceneNode::getIdentifier(){
    return identifier;
}

} /* namespace LayerSceneGraph */
