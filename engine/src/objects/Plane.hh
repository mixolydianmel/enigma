#ifndef PLANE_H
#define PLANE_H

#include "Object.hh"

class Plane : public Object
{
    public:
        Plane(unsigned int type, const std::string& tex = "",
              glm::vec3 pos = glm::vec3(0.f),
              glm::vec4 rot = glm::vec4(0.f, 1.f, 0.f, 0.f),
              glm::vec3 scl = glm::vec3(1.f));

        Plane(unsigned int type, const glm::vec3& clr,
              glm::vec3 pos = glm::vec3(0.f),
              glm::vec4 rot = glm::vec4(0.f, 1.f, 0.f, 0.f),
              glm::vec3 scl = glm::vec3(1.f));

        ~Plane();
    private:
        std::array<float, 32> m_vertices;
        std::array<unsigned int, 6> m_indices;
};

#endif
