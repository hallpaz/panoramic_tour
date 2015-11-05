//
//  Vertex.hpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 19/10/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp


const unsigned int posOffset3D = 0;
const unsigned int texOffset3D = 3*sizeof(float);
const unsigned int normalOffset3D= 5;

struct Vertex {
    float x, y, z;
    float u, v;
    float nx, ny, nz;
};

struct Vertex2D {
    float x, y;
    float u, v;
    float nx, ny, nz;
};

#endif /* Vertex_hpp */
