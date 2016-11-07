//
//  main.cpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 19/10/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <chrono>

#include <FreeImage.h>
#include "Filepaths.h"
#include "LPShader.h"
#include "Mesh.h"
#include "PanoramaViewController.h"

// Headers
#include <iostream>


int main(){
    PanoramaViewController myViewController;
    myViewController.runScene();
    myViewController.endScene();
}