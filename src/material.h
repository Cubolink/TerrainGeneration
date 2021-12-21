//
// Created by major on 21-12-2021.
//

#ifndef TERRAINGEN_MATERIAL_H
#define TERRAINGEN_MATERIAL_H

#include <glm/glm.hpp>
#include "texture.h"
#include "shader.h"

class Material
{
private:
    glm::vec3 ka;
    glm::vec3 kd;
    glm::vec3 ks;
    glm::uint shininess;
    Texture texture;

public:
    Material(float ambiental, float diffuse, float specular, unsigned int shininess, Texture &texture);

    /**
     * Caution: The shader has to be already bound
     */
    void Bind(Shader &shader) const;
};

#endif //TERRAINGEN_MATERIAL_H
