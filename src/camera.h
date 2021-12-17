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
    float dx_dt, dy_dt, dz_dt, max_dEye_dt;
    float phi, theta;  // Sphere coordinates, using eye (x, y, z)
    float dPhi_dt, dTheta_dt, max_dCenter_dt;

public:
    Camera();

    /**
     * Gets the position where the camera is placed
     */
    glm::vec3 getEyeVec3();

    /**
     * Gets the position to where the camera is pointing
     */
    glm::vec3 getCenterVec3() const;

    /**
     * Gets an orientation vector for the camera
     */
    glm::vec3 getUpVec3();

    /**
     * Gets the current view matrix of the ModelViewProjection.
     */
    glm::mat4 getViewMatrix();

    /**
     * Recalculates eye and center position using the speeds and the dt parameter
     * @param dt delta time
     */
    void updateCoords(float dt);

    inline float getRho() const {return 1;}

    inline float getPhi() const {return phi;}

    inline float getTheta() const {return theta;}

    inline float getCX() const {return eye.x;}

    inline float getCY() const {return eye.y;}

    inline float getCZ() const {return eye.z;}

    void setPhi(float value);

    void setTheta(float value);


    /**
     * Sets the eye of the camera to a new position
     * @param x new coordinate
     * @param y new coordinate
     * @param z new coordinate
     */
    void setEye(float x, float y, float z);

    /**
     * Sets a new position to where the camera will point at.
     * @param x new coordinate
     * @param y new coordinate
     * @param z new coordinate
     */
    void setCenter(float x, float y, float z);

    friend class CameraController;
};

#endif //TERRAINGEN_CAMERA_H
