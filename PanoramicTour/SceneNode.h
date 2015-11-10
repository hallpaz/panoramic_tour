/*
 * SceneNode.h
 *
 *  Created on: 19 juin 2013
 *      Author: hallison
 */

#ifndef SCENENODE_H_
#define SCENENODE_H_

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>


class SceneNode {
    
public:
	SceneNode();
	virtual ~SceneNode();
	virtual void draw();
	virtual void update(float clockTick);
	void addChild(SceneNode *s);
	SceneNode *removeChild();

	glm::mat4 getTransform();
	void setTransform(glm::mat4 m, glm::mat4 i);
	glm::mat4 getWorldTransform();
	void setWorldTransform(glm::mat4 m);

	glm::mat4 getInverseTransform();
	glm::mat4 getWorldInverseTransform();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);
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

	SceneNode *getParent();

    SceneNode* getChildByIdentifier(std::string _identifier);
    void setIdentifier(std::string _id);
    std::string getIdentifier();
    std::vector <SceneNode*>::const_iterator getChildteratorStart();
    std::vector <SceneNode*>::const_iterator getChildteratorEnd();
    
protected:
    glm::mat4 transform;
    glm::mat4 worldTransform;
    //Inverse world transformation is necessary for some computations.
    glm::mat4 inverseTransform;
    glm::mat4 inverseWorldTransform;
    
    SceneNode *parent;
    std::vector<SceneNode*> children;
    
    glm::vec3 position;
    
private:
    std::string identifier;
};

#endif /* SCENENODE_H_ */
