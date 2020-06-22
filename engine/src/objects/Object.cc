#include "Object.hh"

Object::Object() :
    m_vbo(0, 0), m_ebo(0, 0), m_shd(""), m_tex("")
{
    m_model = *new glm::mat4(1.0f);

}

void Object::translate(const glm::vec3& translation)
{
    m_model = glm::translate(m_model, translation / m_scale);
    m_position += translation;
}

// TODO: Implement storage of rotation
void Object::rotate(const glm::vec4& rotation)
{
    m_model = glm::rotate(m_model, glm::radians(rotation.x),
            glm::vec3(rotation.y, rotation.z, rotation.w));
}

void Object::scale(const glm::vec3& scaleFactor)
{
    m_model = glm::scale(m_model, scaleFactor);
    m_scale *= scaleFactor;
}

void Object::bindAll() const
{
    m_vao.bind();
    m_vbo.bind();
    m_ebo.bind();

    m_shd.bind();

    if (m_tex.getHeight() != 0 && m_tex.getWidth() != 0)
        m_tex.bind();
}

void Object::unbindAll() const
{
    m_vao.unbind();
    m_vbo.unbind();
    m_ebo.unbind();

    m_shd.unbind();

    if (m_tex.getHeight() != 0 && m_tex.getWidth() != 0)
        m_tex.unbind();
}

void Object::setShaderMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    m_shd.setUniformMat4f("uModel", model);
    m_shd.setUniformMat4f("uView", view);
    m_shd.setUniformMat4f("uProjection", projection);
    return;
}
