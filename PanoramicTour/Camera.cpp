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

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), angleOfView(default_FOV)
{
    this->position = position;
    this->WorldUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
    if(Camera::currentCamera == nullptr) {
        Camera::currentCamera = this;
    }
}

Camera::Camera(unsigned int width, unsigned int height, float angleOfView, float near, float far)
{
    buildPerspective(width, height, angleOfView, near, far);
    if (Camera::currentCamera == nullptr) {
        Camera::currentCamera = this;
    }
}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(this->position, this->position + this->Front, this->Up);
}

const glm::mat4 &Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = Camera::MovementSpeed * deltaTime;
    if (direction == FORWARD)
        currentCamera->position += currentCamera->Front * velocity;
    if (direction == BACKWARD)
        currentCamera->position -= currentCamera->Front * velocity;
    if (direction == LEFT)
        currentCamera->position -= currentCamera->Right * velocity;
    if (direction == RIGHT)
        currentCamera->position += currentCamera->Right * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= Camera::MouseSensitivity;
    yoffset *= Camera::MouseSensitivity;
    
    currentCamera->Yaw   += xoffset;
    currentCamera->Pitch += yoffset;
    
    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (currentCamera->Pitch > 89.0f)
            currentCamera->Pitch = 89.0f;
        if (currentCamera->Pitch < -89.0f)
            currentCamera->Pitch = -89.0f;
    }
    
    // Update Front, Right and Up Vectors using the updated Eular angles
    currentCamera->updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    if (currentCamera->angleOfView >= 1.0f && currentCamera->angleOfView <= 60.0f)
        currentCamera->angleOfView -= yoffset;
    if (currentCamera->angleOfView <= 1.0f)
        currentCamera->angleOfView = 1.0f;
    if (currentCamera->angleOfView >= 60.0f)
        currentCamera->angleOfView = 60.0f;
}

// Calculates the front vector from the Camera's (updated) Eular Angles
void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->Up    = glm::normalize(glm::cross(this->Right, this->Front));
}


void Camera::buildPerspective(unsigned int width, unsigned int height, float angleOfView, float near, float far)
{
    this->width = width;
    this->height = height;
    this->angleOfView = angleOfView;
    this->near = near;
    this->far = far;
    projectionMatrix = glm::perspectiveFov<float>(angleOfView, width, height, this->near, this->far);
}
