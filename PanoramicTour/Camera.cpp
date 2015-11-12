//
//  Camera.cpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 08/11/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#include "Camera.hpp"

float Camera::MovementSpeed = SPEED;
float Camera::MouseSensitivity = SENSITIVTY;
Camera *Camera::currentCamera = nullptr;


Camera::Camera(unsigned int width, unsigned int height, float angleOfView, float near, float far)
{
    this->width = width;
    this->height = height;
    this->angleOfView = angleOfView;
    this->near = near;
    this->far = far;
    projectionMatrix = glm::perspectiveFov<float>(glm::radians(angleOfView), width, height, near, far);
    if (Camera::currentCamera == nullptr) {
        Camera::currentCamera = this;
    }
}

const glm::mat4 &Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
   
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    float fov = currentCamera->angleOfView * (1.0 + yoffset/30.0);
    if(fov < 15.0){
        fov = 15.0;
    }
    if(fov > 90.0){
        fov = 90.0;
    }
    currentCamera->setFov(fov);
}

void Camera::setFov(float fov)
{
    this->angleOfView = fov;
    projectionMatrix = glm::perspectiveFov<float>(glm::radians(angleOfView), width, height, near, far);
}

void Camera::setOrientation(const glm::mat4 matrix)
{
    transform = glm::translate(matrix, position);
}