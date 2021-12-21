//
// Created by major on 21-12-2021.
//

#ifndef TERRAINGEN_LIGHT_H
#define TERRAINGEN_LIGHT_H

#include <glm/glm.hpp>
#include "shader.h"

class Light
{
private:
    glm::vec3 la;
    glm::vec3 ld;
    glm::vec3 ls;
    glm::vec3 position;
    float attenuation_c;
    float attenuation_l;
    float attenuation_q;

public:
    Light(float ambiental, float diffuse, float specular, glm::vec3 position,
          float constant_attenuation, float linear_attenuation, float quadratic_attenuation);

    Light(glm::vec3 ambiental, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position,
          float constant_attenuation, float linear_attenuation, float quadratic_attenuation);

    /**
     *
     * Caution: Binding the shader is not this method's job
     * @param shader
     */
    void Bind(Shader &shader) const;
};

#endif //TERRAINGEN_LIGHT_H
