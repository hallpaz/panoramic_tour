//
//  GLViewController.cpp
//  OpenGL Base
//
//  Created by Hallison da Paz on 27/09/2015.
//  Copyright © 2015 home. All rights reserved.
//

#include "GLViewController.h"
#include <cmath>

GLViewController::GLViewController(){
    this->initGLContext();
}

void GLViewController::initGLContext(unsigned int width, unsigned int height){
    if (!glfwInit()){
        std::cerr << "Failed to initialize context" << std::endl;
        exit(1);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(width, height, "Opengl", nullptr, nullptr);
    
    if (!window)
    {
        glfwTerminate();
        exit(1);
    }
    
    glfwMakeContextCurrent(window);
}


void GLViewController::endScene(){
    
    glfwDestroyWindow(window);
    glfwTerminate();

}

GLViewController::~GLViewController(){
    delete currentShader;
}