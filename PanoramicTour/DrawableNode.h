/*
 * DrawableNode.h
 *
 *  Created on: 23 juil. 2013
 *      Author: hallison
 */

#ifndef DrawableNode_H_
#define DrawableNode_H_

#include <string>
#include <json.hpp>
#include <fstream>
#include <vector>

#include "SceneNode.h"
#include "Mesh.h"
#include "Texture.h"

#include "Vertex.hpp"
#include "Triangle.hpp"

#include <cmath>

#ifndef cimg_use_openexr
    #define cimg_use_openexr
#endif

#include <CImg.h>

//#include "Material.hpp"

/**
  This clas represents all common states between nodes which can be drawn on the screen
 **/
class DrawableNode: public SceneNode {
protected:
    //Material *material;
	Mesh *mesh;
    Texture	*texture;
    std::vector<Vertex> vertexBuffer;
    std::vector<Triangle> indexBuffer;

public:
    DrawableNode(std::string description);
	virtual ~DrawableNode();
	void draw();
    
    void createMeshFromDepthImage(std::string image_path);
    void createTextureFromRGBImage(std::string image_path);
    void *vertexBufferData();
    void *indexBufferData();
    Texture *getTexture();
    
    unsigned long numOfIndices();
    unsigned long sizeOfIndices();
    unsigned long sizeOfVertices();
	
	void setTexture(Texture *texture);
    //void setMaterial(Material *material);
};

#endif /* DrawableNode_H_ */
