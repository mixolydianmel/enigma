#ifndef CAMERA_H
#define CAMERA_H

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

class Camera
{
    public:
        Camera();
        Camera(glm::vec3 position, float fov = 45.f, glm::vec3 direction = glm::vec3(0.f, 0.f, -1.f));

        inline glm::vec3& getPosition() { return m_position; }
        inline glm::vec3& getDirection() { return m_direction; }

        inline float getPitch() { return m_pitch; }
        inline float getYaw() { return m_yaw; }

        inline glm::vec3& getRight() { return m_right; }
        inline glm::vec3& getUp() { return m_up; }

        inline glm::mat4& getViewMatrix() { return m_view; }
        inline float getFOV() { return m_fov; }

        void setPosition(glm::vec3 position);
        void setDirection(glm::vec3 direction);

        void setPitch(float pitch);
        void setYaw(float yaw);

        void calculateDirection();
    private:
        glm::vec3 m_position;
        glm::vec3 m_direction;

        float m_pitch;
        float m_yaw;

        glm::vec3 m_right;
        glm::vec3 m_up;

        glm::mat4 m_view;
        float m_fov;

        void recalculateView();
};

#endif
