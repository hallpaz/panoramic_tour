//
//  Vertex.hpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 19/10/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <glm/glm.hpp>

const unsigned int posOffset3D = 0;
const unsigned int texOffset3D = 3*sizeof(float);
const unsigned int normalOffset3D= 5;

struct Vertex {
    // position coordinates
    glm::vec3 position;
    // texture coordinates
    glm::vec2 texCoords;
    // normal coordinates
    glm::vec3 normal;
};

struct Vertex2D {
    // position coordinates
    glm::vec2 position;
    // texture coordinates
    glm::vec2 texCoords;
    // normal coordinates
    glm::vec3 normal;
};

#endif /* Vertex_hpp */
