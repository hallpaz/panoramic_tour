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

#include "SceneNode.h"

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
const float default_FOV  =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera : public SceneNode
{
public:
    
    Camera(unsigned int width = 360, unsigned int height = 480, float angleOfView = 45.0, float near = 0.1, float far = 50);
    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    static void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    static void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    static void ProcessMouseScroll(float yoffset);
    
    
  
    void setViewMatrix(const glm::mat4 matrix);
    void setOrientation(const glm::mat4 matrix);
    void setOrientation();
    void setProjectionMatrix(const glm::mat4 matrix);
    void setNear(float n);
    void setFar(float f);
    void setFov(float fov);
    void setResolution(float width, float height);
    
    
    unsigned int getWidth();
    unsigned int getHeight();
    float getAngleOfView();
    float getAspectRatio();
    float getNearDistance();
    float getFarDistance();
    glm::mat4 getViewMatrix();
    const glm::mat4 &getProjectionMatrix();
    
    glm::vec3 &getHorizontalDirection();
    glm::vec3 &getLookDirection();
    glm::vec3 &getUpDirection();
    
protected:
   
    
    glm::mat4 projectionMatrix;
    
    float near, far, angleOfView;
    unsigned int width, height;
    static float MovementSpeed;
    static float MouseSensitivity;
    static Camera *currentCamera;
    
    // Eular Angles
    // Camera Attributes
    /*glm::vec3 Front;
     glm::vec3 Up;
     glm::vec3 Right;
     glm::vec3 WorldUp;*/
    //float Yaw;
    //float Pitch;
    // Camera options
private:
    // Calculates the front vector from the Camera's (updated) Eular Angles
    //void updateCameraVectors();
    
};


#endif /* Camera_hpp */
