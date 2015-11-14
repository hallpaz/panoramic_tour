/*
 * DrawableNode.h
 *
 *  Created on: 23 juil. 2013
 *      Author: hallison
 */

#ifndef DrawableNode_H_
#define DrawableNode_H_

#include "SceneNode.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.hpp"

/**
  This clas represents all common states between nodes which can be drawn on the screen
 **/
class DrawableNode: public SceneNode {
protected:
	Mesh *mesh;
    Material *material;
    Texture	*texture;

public:
	DrawableNode();
	virtual ~DrawableNode();
	void draw();
	
	void setTexture(Texture *texture);
    void setMaterial(Material *material);
};

#endif /* DrawableNode_H_ */
