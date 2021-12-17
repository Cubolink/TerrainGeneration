//
// Created by major on 16-12-2021.
//

#ifndef TERRAINGEN_CAMERA_H
#define TERRAINGEN_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
    glm::vec3 eye;
    float rho, phi, theta;  // Sphere coordinates, using eye (x, y, z)

public:
    Camera();

    glm::vec3 getEyeVec3();

    glm::vec3 getCenterVec3() const;

    glm::vec3 getUpVec3();

    glm::mat4 getViewMatrix();

    inline float getRho() const {return rho;}

    inline float getPhi() const {return phi;}

    inline float getTheta() const {return theta;}

    inline float getCX() const {return eye.x;}

    inline float getCY() const {return eye.y;}

    inline float getCZ() const {return eye.z;}

    void setRho(float value);

    void setPhi(float value);

    void setTheta(float value);

    void setEye(float x, float y, float z);

    void setCenter(float x, float y, float z);
};

#endif //TERRAINGEN_CAMERA_H
