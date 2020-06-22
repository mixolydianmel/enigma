#include "Camera.hh"
#include <iostream>

Camera::Camera() :
    m_fov(45.f)
{
    m_position = glm::vec3(0.f, 0.f, 0.f);
    m_direction = glm::vec3(0.f, 0.f, -1.f);

    m_right = glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), m_direction));
    m_up = glm::cross(m_direction, m_right);

    m_view = glm::lookAt(m_position, m_position + m_direction, m_up);
}

Camera::Camera(glm::vec3 position, float fov, glm::vec3 direction) :
    m_fov(fov)
{
    m_position = position;
    m_direction = direction;

    m_right = glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), m_direction));
    m_up = glm::cross(m_direction, m_right);

    m_view = glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera::recalculateView()
{
    m_right = glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), m_direction));
    m_up = glm::cross(m_direction, m_right);

    m_view = glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera::setPosition(glm::vec3 position)
{
    m_position = position;
    recalculateView();
}

void Camera::setDirection(glm::vec3 direction)
{
    m_direction = glm::normalize(direction);
    recalculateView();
}

void Camera::setPitch(float pitch)
{
    m_pitch = pitch;
}

void Camera::setYaw(float yaw)
{
    m_yaw = yaw;
}

void Camera::calculateDirection()
{
    m_direction = glm::normalize(
        glm::vec3(
            cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
            sin(glm::radians(m_pitch)),
            sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))
    ));
    recalculateView();
}
