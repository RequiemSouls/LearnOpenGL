#include "camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), moveSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
    std::cout << front.x << " " << front.y << " " << front.z << std::endl;
    std::cout << position.x << " " << position.y << " " << position.z << std::endl;
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyBoard(Camera_Movement direction, float deltaTime) {
    float velocity = moveSpeed * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    else if (direction == BACKWARD)
        position -= front * velocity;
    else if (direction == LEFT)
        position -= right * velocity;
    else if (direction == RIGHT)
        position += right * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yOffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 _front;
    _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    _front.y = sin(glm::radians(pitch));
    _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(_front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
