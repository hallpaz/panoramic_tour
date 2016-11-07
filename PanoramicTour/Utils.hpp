//
//  Utils.hpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 06/11/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <vector>
#include <string>
#include "Vertex.hpp"
#include "Triangle.hpp"

void write_Ply(std::vector<Vertex> &vertices, std::vector<Triangle> &faces, std::string filename);
void write_OFF(std::vector<Vertex> &vertices, std::vector<Triangle> &faces, std::string filename);


#endif /* Utils_hpp */
