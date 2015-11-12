//
//  Mesh.h
//  PanoramicTour
//
//  Created by Hallison da Paz on 19/10/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include <vector>
#include "Vertex.hpp"
#include "Triangle.hpp"

class Mesh {
private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> faces;
    
public:
    Mesh();
    virtual ~Mesh();
    unsigned int numVertices();
    unsigned int numIndices();
    void addVertex(Vertex v);
    void setVertex(Vertex* array_vertices, size_t count);
    void setIndices(unsigned int* array_indices, size_t count);
    const Vertex* getData() const;
};

#endif /* Mesh_h */
