//
//  PanoramaViewController.cpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 23/10/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#include "PanoramaViewController.h"
#include "Filepaths.h"

#include <cmath>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Utils.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>


float PanoramaViewController::fieldOfView = 45.0;
bool PanoramaViewController::perspectiveChanged = false;
float PanoramaViewController::movement[2] = {0.0, 0.0};
float PanoramaViewController::verticalAngle = 0.0;
float PanoramaViewController::horizontalAngle = 0.0;
double PanoramaViewController::lastMouseX = 800.0/2.0;
double PanoramaViewController::lastMouseY = 600.0/2.0;


void enableCulling(int windingMode, int orientation);
void enableDepthTest(int depthFunction);
void configTexParams(int texture_wrap_s, int texture_wrap_t, int texture_min_filter, int texture_mag_filter);

PanoramaViewController::PanoramaViewController(){
    
    currentCamera = new Camera(800, 600, PanoramaViewController::fieldOfView);
    DrawableNode myScene("/Users/hallpaz/Workspace/PanoramicTour/PanoramicTour/scene_descriptions/cameraA.json");
    panoramas.push_back(myScene);
    
    currentShader = new LPShader(PATH_BASIC_TEXTURE_VSH, PATH_BASIC_TEXTURE_FSH);
    currentShader->linkProgram();
    GLuint shaderProgram = currentShader->getProgram();
    glUseProgram(shaderProgram);
    
    prepareVAOs();
    
    int width, height;
    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(PATH_Background_rgbA_PNG.c_str(), 0),
                                      PATH_Background_rgbA_PNG.c_str());
    width = FreeImage_GetWidth(bitmap);
    height = FreeImage_GetHeight(bitmap);
    
    // Load textures
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                 width, height,
                 0, GL_BGR, GL_UNSIGNED_BYTE, FreeImage_GetBits(bitmap));
    
    FreeImage_Unload(bitmap);
    glUniform1i(glGetUniformLocation(shaderProgram, "texSampler"), 0);
    
    myTextures.push_back(texture);
    
    configTexParams(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
    
    enableCulling(GL_CW, GL_BACK);
    enableDepthTest(GL_LESS);
    
    //currentCamera->setPosition(myScene.getPosition());
    
    updateShaderMatrices();
    
    configureInput();
    glfwGetCursorPos(window, &PanoramaViewController::lastMouseX, &PanoramaViewController::lastMouseY);
    
}

void PanoramaViewController::updateShaderMatrices()
{
    GLint matrixHandle = glGetUniformLocation(currentShader->getProgram(), "projectionMatrix");
    glUniformMatrix4fv(matrixHandle, 1, GL_FALSE, glm::value_ptr(currentCamera->getProjectionMatrix()) );
    
    matrixHandle = glGetUniformLocation(currentShader->getProgram(), "viewMatrix");
    glUniformMatrix4fv(matrixHandle, 1, GL_FALSE, glm::value_ptr(currentCamera->getTransform()));
}


void PanoramaViewController::update(float rate){
    
    currentCamera->setPosition(movement[1], -1.15, movement[0]);
    
    glm::mat4 orientationMatrix = glm::eulerAngleXYZ<float>(glm::radians(PanoramaViewController::verticalAngle),
                                                     glm::radians(PanoramaViewController::horizontalAngle),
                                                            0.0);
    currentCamera->setOrientation(orientationMatrix);
    
    updateShaderMatrices();
}

void PanoramaViewController::draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (int i = 0; i < panoramas.size(); ++i) {
        
        glBindVertexArray(myVAOs[i]);
        glBindTexture(GL_TEXTURE_2D, myTextures[i]);
        
        GLint matrixHandle = glGetUniformLocation(currentShader->getProgram(), "modelMatrix");
        glUniformMatrix4fv(matrixHandle, 1, GL_FALSE, glm::value_ptr(panoramas[i].getTransform()) );
        
        glDrawElements(GL_TRIANGLES, (GLsizei) panoramas[0].numOfIndices(), GL_UNSIGNED_INT, 0);
    }
    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glfwSwapBuffers(window);
}

void PanoramaViewController::runScene(){
    glfwSwapInterval(1); //not sure if should keep it (vertical sync)
    
    while (!glfwWindowShouldClose(window))
    {
        update(1/30.0);
        draw();
        glfwPollEvents();
    }
}


void PanoramaViewController::scroll_callback(GLFWwindow *window, double xoffset, double yoffset){
    Camera::ProcessMouseScroll(yoffset);
}

void PanoramaViewController::cursor_position_callback(GLFWwindow *window, double xpos, double ypos){
    float mouseSpeed = 0.1;
    float xOffset = xpos - lastMouseX;
    float yOffset = ypos - lastMouseY;
    PanoramaViewController::horizontalAngle += mouseSpeed * xOffset;
    PanoramaViewController::verticalAngle   += mouseSpeed * yOffset;
    lastMouseX = xpos;
    lastMouseY = ypos;
}

void PanoramaViewController::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    float speed = 0.2;
    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        //position += direction * deltaTime * speed;
        PanoramaViewController::movement[0] += speed;
    }
    // Move backward
    if (key == ( GLFW_KEY_DOWN ) && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        //position -= direction * deltaTime * speed;
        PanoramaViewController::movement[0] -= speed;
    }
    // Strafe right
    if (key == ( GLFW_KEY_RIGHT ) && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        //position += right * deltaTime * speed;
        PanoramaViewController::movement[1] -= speed;
    }
    // Strafe left
    if (key == ( GLFW_KEY_LEFT ) && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        //position -= right * deltaTime * speed;
        PanoramaViewController::movement[1] += speed;
    }
    //Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime);
    
    if (key == ( GLFW_KEY_ESCAPE ) && (action == GLFW_PRESS)){
        glfwSetWindowShouldClose(window, true);
    }
}

void PanoramaViewController::configureInput(){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetScrollCallback(window, &PanoramaViewController::scroll_callback);
    glfwSetCursorPosCallback(window, &PanoramaViewController::cursor_position_callback);
    glfwSetKeyCallback(window, &PanoramaViewController::key_callback);
}

PanoramaViewController::~PanoramaViewController()
{
    delete currentCamera;
}

void enableCulling(int windingMode, int orientation){
    glEnable(GL_CULL_FACE);
    glFrontFace(windingMode);
    glCullFace(orientation);
}

void enableDepthTest(int depthFunction){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(depthFunction);
}

void configTexParams(int texture_wrap_s, int texture_wrap_t, int texture_min_filter, int texture_mag_filter){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void PanoramaViewController::prepareVAOs(){
    for(std::vector<DrawableNode>::iterator pano_it = panoramas.begin(); pano_it != panoramas.end(); ++pano_it){
        GLuint vao;
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        // Create a Vertex Buffer Object and copy the vertex data to it
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, pano_it->sizeOfVertices(), pano_it->vertexBufferData(), GL_STATIC_DRAW);
        
        // Create an element array
        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, pano_it->sizeOfIndices(), pano_it->indexBufferData(), GL_STATIC_DRAW);
        
        // Specify the layout of the vertex data
        GLint posAttrib = glGetAttribLocation(currentShader->getProgram(), "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        
        GLint texAttrib = glGetAttribLocation(currentShader->getProgram(), "texcoord");
        glEnableVertexAttribArray(texAttrib);
        glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(texOffset3D));
        
        myVAOs.push_back(vao);
        
    }
}
