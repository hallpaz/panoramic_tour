//
//  Mesh.cpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 19/10/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#include "Mesh.h"

Mesh::Mesh(){
    //do nothing
}

Mesh::~Mesh(){
    
}

void Mesh::addVertex(Vertex v){
    vertices.push_back(v);
}


const Vertex* Mesh::getData() const{
    return &(vertices.front());
}


void Mesh::setVertex(Vertex *array_vertices, size_t count){
    vertices.assign(array_vertices, array_vertices + count);
}

void Mesh::setFaces(Triangle *array_indices, size_t count){
    faces.assign(array_indices, array_indices + count);
}