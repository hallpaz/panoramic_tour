/*
 * SceneNode.cpp
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#include "SceneNode.h"
#include <glm/gtx/euler_angles.hpp>


using namespace std;

/**
 * Dafault constructor. Instances  a transform and a world transform matrix and
 * set its parent as NULL.
 */
SceneNode::SceneNode() {
	parent = nullptr;
    transform = glm::mat4(1.0);
    inverseTransform = glm::mat4(1.0);
    worldTransform = glm::mat4(1.0);
    inverseWorldTransform = glm::mat4(1.0);
    position = glm::vec3(0, 0, 0);
}

/**
 * Destructor. Releases and deletes all children of this node.
 */
SceneNode::~SceneNode() {
	for(unsigned int i = 0; i < children.size (); ++ i) {
		delete children [ i ];
	}
}

/**
 * Adds another node as a child of this node.
 * @param s The node to be inserted
 */
void SceneNode::addChild(SceneNode *s) {
	s->parent = this;
	children.push_back(s);
}

/**
 * Removes the last child added from this node children vector.
 */
SceneNode *SceneNode::removeChild(){
	SceneNode *s = children.back();
	s->parent = NULL;
	children.pop_back();
	return s;
}

/**
 * Returns the local transformation matrix of this node
 * @return transform The local transforma
 */
glm::mat4 SceneNode::getTransform() {
	return transform;
}

/**
 * Sets a new transform matrix for this node.
 * @param m,i The 4x4 matrix transform and its inverse
 */
void SceneNode::setTransform(glm::mat4 m, glm::mat4 i) {
	transform = m;
	inverseTransform = i;
}

/**
 * Returns the world transform matrix of this node. This matrix represents the transformation
 * of this node relative to the complete scene.
 * @return worldTransform The 4x4 matrix which
 */
glm::mat4 SceneNode::getWorldTransform() {
	return worldTransform;
}
/**
 * Sets a new world transform for this node.
 * @param Matrix4 m A 4x4 matrix
 */
void SceneNode::setWorldTransform(glm::mat4 m) {
	worldTransform = m;
}


/**
 * Return this node's parent.
 * @result parent This node's parent
 */
SceneNode* SceneNode::getParent() {
	return parent;
}
/**
 * Returns this node position in its local coordinate system.
 * @result position A 3 dimensional vector with node's position coordinates
 */
    glm::vec3 SceneNode::getPosition() {
	return position;
}

/**
 * Sets this node position equal to given vector values
 */
    void SceneNode::setPosition(glm::vec3 pos) {
	position = pos;
    
    transform = glm::translate(transform, position);
    inverseTransform =  glm::translate(inverseTransform, -position);
}
/**
 * Sets this node position coordinates given by x, y, z
 */
void SceneNode::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
    
    glm::translate(transform, position);
    glm::translate(inverseTransform, -position);
}
/**
 * Translate this node position by values specified
 */
void SceneNode::translateBy(float x, float y, float z) {
    glm::vec3 translationOffset(x, y, z);
    position = position + translationOffset;
	
    glm::translate(transform, translationOffset);
    glm::translate(inverseTransform, -translationOffset);
}
/**
 * Scale this node uniformly
 */
void SceneNode::scaleBy(float scaleFactor) {
    glm::scale(transform, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    glm::scale(inverseTransform, glm::vec3(1/scaleFactor, 1/scaleFactor, 1/scaleFactor));
}

void SceneNode::scaleBy(float sX, float sY, float sZ) {
    glm::scale(transform, glm::vec3(sX, sY, sZ));
    glm::scale(inverseTransform, glm::vec3(1/sX, 1/sY, 1/sZ));
}

void SceneNode::scaleX(float sX) {
    glm::scale(transform, glm::vec3(sX, 1, 1));
    glm::scale(inverseTransform, glm::vec3(1/sX, 1, 1));
}

void SceneNode::scaleY(float sY) {
    glm::scale(transform, glm::vec3(1, sY, 1));
    glm::scale(inverseTransform, glm::vec3(1, 1/sY, 1));
}

void SceneNode::scaleZ(float sZ) {
    glm::scale(transform, glm::vec3(1, 1, sZ));
    glm::scale(inverseTransform, glm::vec3(1, 1, 1/sZ));
}
/**
 * Makes a free rotation in this node, specifying euler angles
 */
void SceneNode::rotateBy(float alpha, float beta, float gamma) {
    glm::mat4 rotation = glm::eulerAngleXYZ(alpha, beta, gamma);
    transform = rotation * transform;
    inverseTransform = inverseTransform * rotation;
    //TODO: implement rotation
}
/**
 * Rotates node around X axis by an angle
 */
void SceneNode::rotateAroundX(float rX) {
    glm::mat4 rotation = glm::eulerAngleX(rX);
    transform = rotation * transform;
    inverseTransform = inverseTransform * rotation;
}
/**
 * Rotates node around Y axis by an angle
 */
void SceneNode::rotateAroundY(float rY) {
    glm::mat4 rotation = glm::eulerAngleY(rY);
    transform = rotation * transform;
    inverseTransform = inverseTransform * rotation;
}
/**
 * Rotates node around Z axis by an angle
 */
void SceneNode::rotateAroundZ(float rZ) {
    glm::mat4 rotation = glm::eulerAngleZ(rZ);
    transform = rotation * transform;
    inverseTransform = inverseTransform * rotation;
}

vector <SceneNode*>::const_iterator SceneNode::getChildteratorStart(){
		return children.begin();
}

glm::mat4 SceneNode::getInverseTransform() {
	return inverseTransform;
}

glm::mat4 SceneNode::getWorldInverseTransform() {
	return inverseWorldTransform;
}

void SceneNode::update(float clockTick) {
	if(parent){
		worldTransform = (parent->getWorldTransform())*transform;
		inverseWorldTransform = inverseTransform*parent->getWorldInverseTransform();
	}
	else{
		worldTransform = transform;
		inverseWorldTransform = inverseTransform;
	}
    vector<SceneNode*>::const_iterator nodeIterator;
    for(nodeIterator = getChildteratorStart(); nodeIterator != getChildteratorEnd(); ++nodeIterator)
    {
        (*nodeIterator)->update(clockTick);
    }
}
void SceneNode::draw(){
    vector<SceneNode*>::const_iterator nodeIterator;
    for(nodeIterator = getChildteratorStart(); nodeIterator != getChildteratorEnd(); ++nodeIterator)
    {
        (*nodeIterator)->draw();
    }
}

vector<SceneNode*>::const_iterator SceneNode::getChildteratorEnd() {
		return children.end();
}
    
SceneNode* SceneNode::getChildByIdentifier(string _identifier)
{
    SceneNode *searchedNode = nullptr;
    vector<SceneNode*>::const_iterator iterator;
    for (iterator = getChildteratorStart(); iterator != getChildteratorEnd(); ++iterator) {
        SceneNode *node = *iterator;
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
void SceneNode::setIdentifier(string _id){
    identifier = _id;
}
/**
 * Returns this node's string identifier
 * @return identifier A copy of identifier attribute
 */
string SceneNode::getIdentifier(){
    return identifier;
}
