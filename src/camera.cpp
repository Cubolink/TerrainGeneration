//
// Created by major on 16-12-2021.
//

#include "camera.h"

#include <iostream>
#include <cmath>

Camera::Camera()
: eye(0, 0, 0), rho(1), phi(0), theta(0)
{

}

glm::vec3 Camera::getEyeVec3() {
    return eye;
}

glm::vec3 Camera::getCenterVec3() const {
    return {rho * std::cos(phi) * std::sin(theta) + eye.x,
            rho * std::sin(phi) * std::sin(theta) + eye.y,
            rho * std::cos(theta) + eye.z};
}

glm::vec3 Camera::getUpVec3() {
    return {.0f, 1.0f, .0f};
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(eye, getCenterVec3(), getUpVec3());
}

void Camera::setRho(float value) {
    rho = value;
}

void Camera::setPhi(float value) {
    phi = value;
}

void Camera::setTheta(float value) {
    theta = value;
}

void Camera::setEye(float x, float y, float z) {
    eye.x = x;
    eye.y = y;
    eye.z = z;
}

void Camera::setCenter(float x, float y, float z) {
    x -= eye.x;
    y -= eye.y;
    z -= eye.z;

    rho = (float) std::sqrt(x*x + y*y + z*z);
    phi = (float) std::atan2(y, x);
    theta = (float) std::atan(std::sqrt(x*x + y*y)/std::sqrt(z*z));
    if (z < 0)
        theta = glm::radians(180.0f) - theta;

}

