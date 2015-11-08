//
//  Utils.cpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 06/11/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//


#include <fstream>
#include "Utils.hpp"


void write_Ply(std::vector<Vertex> &vertices, std::vector<Triangle> &faces, std::string filename)
{
    std::ofstream outfile;
    outfile.open(filename.c_str(), std::ios::out);
    
    outfile << "ply" << std::endl
    << "format ascii 1.0" << std::endl
    << "element vertex "<< vertices.size() << std::endl
    << "property float x" << std::endl
    << "property float y" << std::endl
    << "property float z" << std::endl
    << "element face " << faces.size() << std::endl
    << "property list uchar int vertex_index" << std::endl
    << "property list uchar float texcoord" << std::endl
    << "end_header" << std::endl;
    for ( std::vector<Vertex>::iterator v_it = vertices.begin(); v_it != vertices.end(); ++v_it) {
        outfile << v_it->x << " " << v_it->y << " " << v_it->z << std::endl;
    }
    
    for ( std::vector<Triangle>::iterator f_it = faces.begin(); f_it != faces.end(); ++f_it) {
        outfile << "3" << " " << f_it->a << " " << f_it->b << " " << f_it->c << std::endl;
    }
    for ( std::vector<Vertex>::iterator v_it = vertices.begin(); v_it != vertices.end(); ++v_it) {
        outfile << v_it->u << " " << v_it->v << std::endl;
    }
    
    
}