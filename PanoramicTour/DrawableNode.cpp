/*
 * DrawableNode.cpp
 *
 *  Created on: 23 juil. 2013
 *      Author: hallison
 */

#include "DrawableNode.h"


DrawableNode::DrawableNode() {
	mesh = nullptr;
    texture = nullptr;
    material = nullptr;
}

DrawableNode::~DrawableNode() {
    delete texture;
}

/**
 * Updates transformation matrix and draws mesh
 */
void DrawableNode::draw(){

}


/**
 * Sets a new texture for this drawable node
 */
   
void DrawableNode::setTexture(Texture* texture) {
    this->texture = texture;
}