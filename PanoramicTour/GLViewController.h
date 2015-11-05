//
//  GLViewController.h
//  OpenGL Base
//
//  Created by Hallison da Paz on 27/09/2015.
//  Copyright © 2015 home. All rights reserved.
//


#ifndef GLViewController_h
#define GLViewController_h

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <iostream>
#include "LPShader.h"




using namespace LayerSceneGraph;

class GLViewController {
protected:
    LPShader *currentShader;
    GLFWwindow* window;
    void initGLContext(unsigned int width = 800, unsigned int height = 600);
    
public:
    GLViewController();
    virtual ~GLViewController();
    
    virtual void update(float rate) = 0;
    virtual void draw() = 0;
    virtual void runScene() = 0;
    virtual void endScene();
};

#endif /* GLViewController_h */