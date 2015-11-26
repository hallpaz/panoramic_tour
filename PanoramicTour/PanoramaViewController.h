//
//  PanoramaViewController.hpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 23/10/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#ifndef PanoramaViewController_h
#define PanoramaViewController_h

#include <FreeImage.h>
#include "GLViewController.h"
#include "Mesh.h"
#include "Vertex.hpp"
#include "Triangle.hpp"

#include "Camera.hpp"
#include "DrawableNode.h"


struct SceneBatch;

class PanoramaViewController : public GLViewController {
private:
    GLuint vao;
    std::vector<Vertex> vertices;
    std::vector<Triangle> faces;
    std::vector<DrawableNode> panoramas;
    
    std::vector<GLuint> myVAOs;
    std::vector<GLuint> myTextures;
    std::vector<SceneBatch> mySceneBatches;
    
protected:
    static float fieldOfView;
    static bool perspectiveChanged;
    static float movement[2];
    static float horizontalAngle;
    static float verticalAngle;
    static double lastMouseX;
    static double lastMouseY;
    
    Camera *currentCamera;
    void configureInput();
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    void prepareVAOs();
    
public:
    PanoramaViewController();
    virtual ~PanoramaViewController();
    virtual void update(float rate);
    virtual void draw();
    virtual void runScene();
    
    void updateShaderMatrices();
    
};

#endif /* PanoramaViewController_h */
