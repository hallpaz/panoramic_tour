//
//  Camera.hpp
//  PanoramicTour
//
//  Created by Hallison da Paz on 08/11/2015.
//  Copyright © 2015 Visgraf. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW        = -90.0f;
const float PITCH      =  0.0f;
const float SPEED      =  3.0f;
const float SENSITIVTY =  0.25f;
const float ZOOM       =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    
    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();
    
    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    static void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    
    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    static void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    
    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    static void ProcessMouseScroll(float yoffset);
    
protected:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Eular Angles
    float Yaw;
    float Pitch;
    // Camera options
    static float MovementSpeed;
    static float MouseSensitivity;
    float Zoom;
    static Camera *currentCamera;
    
private:
    // Calculates the front vector from the Camera's (updated) Eular Angles
    void updateCameraVectors();
};


#endif /* Camera_hpp */
