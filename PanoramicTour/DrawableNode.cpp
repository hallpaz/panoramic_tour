/*
 * DrawableNode.cpp
 *
 *  Created on: 23 juil. 2013
 *      Author: hallison
 */

#include "DrawableNode.h"

using json = nlohmann::json;
using namespace cimg_library;

DrawableNode::DrawableNode(std::string descriptionFile) {
    std::ifstream descriptionStream(descriptionFile);
    json scene_json;
    
    if (descriptionStream.is_open()) {
        //std::cout << descriptionStream << std::endl;
        
        descriptionStream >> scene_json;
       
    }
    else{
        std::cout << "Failed to open file description" << std::endl;
    }
    
    createMeshFromDepthImage(scene_json["depth_images_files"][0]);
    std::string rgbImagePath = scene_json["rgb_images_files"][0];
    texture = new Texture( rgbImagePath );
    
    this->setPosition(glm::vec3(scene_json["model_position"]["x"],
                                scene_json["model_position"]["y"],
                                scene_json["model_position"]["z"] ));
    
	mesh = nullptr;
    //texture = nullptr;
    //material = nullptr;
}


void DrawableNode::createMeshFromDepthImage(std::string image_path){
    CImg<float> image(image_path.c_str());
    unsigned int paralelos = image.height();
    unsigned int meridianos = image.width();
    
    float theta = 0.005;
    float phi = 0.00;
    
    int j = 0; int i = 0;
    float u, v, depth;
    for(theta = 0.00005; theta < M_PI; theta += (M_PI - 0.0001)/(paralelos-1)){
        for(phi = 0.0; phi < 2*M_PI; phi += 2*M_PI/meridianos){
            //Position coordinates
            depth = image(i, j);

            u = phi/(2*M_PI);
            v = 1.0 - theta/M_PI;
            
            vertexBuffer.push_back(Vertex{ glm::vec3(depth*sin(theta)*sin(phi), depth*cos(theta), depth*sin(theta)*cos(phi)),
                glm::vec2(u, v),
                glm::vec3(0.0, 0.0, 0.0) });
            ++i;
        }
        phi = 0.0;
        i = 0;
        depth = image(i, j);
        ++j;

        u = 1.0;
        v = 1.0 - theta/M_PI;
        
        vertexBuffer.push_back(Vertex{ glm::vec3(depth*sin(theta)*sin(phi), depth*cos(theta), depth*sin(theta)*cos(phi)),
            glm::vec2(u, v),
            glm::vec3(0.0, 0.0, 0.0) });
    }
    //compute triangulation
    double distanceThreshold = 0.50;
    double mindist = 100.0, maxdist = -1.0;
    for(i = 0; i < paralelos; ++i){
        for (j = 0; j < meridianos; ++j) {
            if( ((j+1) < meridianos)){
                double currentDistance = std::abs(image(j,i) - image(j+1, i));
                if(currentDistance < mindist){
                    mindist = currentDistance;
                }
                if (currentDistance > maxdist) {
                    maxdist = currentDistance;
                }
                if ((currentDistance) > distanceThreshold ) {
                    std::cout << i << ", " << j << std::endl;
                    continue;
                }
            }
            if(i+1 < paralelos){
                indexBuffer.push_back( { i*(meridianos+1) + j, (i+1)*(meridianos+1) +j, i*(meridianos+1) + j+1  });
            }
            
            if(i-1 > 0){
                indexBuffer.push_back( {(i-1)*(meridianos+1) + j+1, i*(meridianos+1) + j, i*(meridianos+1) + j+1});
            }
        }
    }
    std::cout << "min: " << mindist << " max: " << maxdist << std::endl;
    //std::cout << "indices vector size: " << indexBuffer.size() << std::endl;
    
}

DrawableNode::~DrawableNode() {
//    if(texture != nullptr) {
//        texture->unload();
//        texture = nullptr;
//    }
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

void *DrawableNode::vertexBufferData(){
    return &vertexBuffer.front();
}

void *DrawableNode::indexBufferData(){
    return &indexBuffer.front();
}

Texture *DrawableNode::getTexture(){
    return texture;
}

unsigned long DrawableNode::numOfIndices(){
    return indexBuffer.size()*3;
}

unsigned long DrawableNode::sizeOfIndices(){
    return indexBuffer.size()*sizeof(Triangle);
}
unsigned long DrawableNode::sizeOfVertices(){
    return vertexBuffer.size()*sizeof(Vertex);
}