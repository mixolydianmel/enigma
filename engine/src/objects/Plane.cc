#include "Plane.hh"
#include <iostream>

Plane::Plane(unsigned int type, const std::string& tex,
        glm::vec3 pos, glm::vec4 rot, glm::vec3 scl)
{
    m_model = *new glm::mat4(1.f);

    m_position = pos;
    m_rotation = rot;
    m_scale = scl;

    m_vertices = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.f, 0.f, 1.f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.f, 0.f, 1.f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.f, 0.f, 1.f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.f, 0.f, 1.f
    };

    m_indices = {
        0, 1, 2,
        2, 3, 0
    };

    m_vao = *new VertexArray();
    m_vao.bind();

    m_vbo = *new VertexBuffer(&m_vertices.front(), m_vertices.size() * sizeof(float));
    m_vbo.bind();

    m_ebo = *new ElementBuffer(&m_indices.front(), m_indices.size());
    m_ebo.bind();

    VertexAttribute position(0, 3, GL_FLOAT, GL_FALSE);
    VertexAttribute texCoords(1, 2, GL_FLOAT, GL_FALSE);
    VertexAttribute normals(2, 3, GL_FLOAT, GL_FALSE);
    m_vao.pushAttribute(position);
    m_vao.pushAttribute(texCoords);
    m_vao.pushAttribute(normals);

    m_vao.setPointers();

    m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, glm::radians(m_rotation.x),
            glm::vec3(m_rotation.y, m_rotation.z, m_rotation.w));
    m_model = glm::scale(m_model, m_scale);

    if (type == OBJECT_TEXTURE_LIT)
        m_shd = *new Shader("src/objects/Object_texture_lit.glsl");
    else if (type == OBJECT_TEXTURE_UNLIT)
        m_shd = *new Shader("src/objects/Object_texture.glsl");
    else
        std::cerr << "Error: Invalid type in object constructor" << std::endl;

    m_shd.bind();

    m_tex = *new Texture(tex);
    m_tex.bind();
}

Plane::Plane(unsigned int type, const glm::vec3& clr,
        glm::vec3 pos, glm::vec4 rot, glm::vec3 scl)
{
    m_model = *new glm::mat4(1.f);

    m_position = pos;
    m_rotation = rot;
    m_scale = scl;

    m_vertices = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.f, 0.f, 1.f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.f, 0.f, 1.f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.f, 0.f, 1.f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.f, 0.f, 1.f
    };

    m_indices = {
        0, 1, 2,
        2, 3, 0
    };

    m_vao = *new VertexArray();
    m_vao.bind();

    m_vbo = *new VertexBuffer(&m_vertices.front(), m_vertices.size() * sizeof(float));
    m_vbo.bind();

    m_ebo = *new ElementBuffer(&m_indices.front(), m_indices.size());
    m_ebo.bind();

    VertexAttribute position(0, 3, GL_FLOAT, GL_FALSE);
    VertexAttribute texCoords(1, 2, GL_FLOAT, GL_FALSE);
    VertexAttribute normals(2, 3, GL_FLOAT, GL_FALSE);
    m_vao.pushAttribute(position);
    m_vao.pushAttribute(texCoords);
    m_vao.pushAttribute(normals);

    m_vao.setPointers();

    m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, glm::radians(m_rotation.x),
            glm::vec3(m_rotation.y, m_rotation.z, m_rotation.w));
    m_model = glm::scale(m_model, m_scale);

    if (type == OBJECT_COLOR_LIT)
        m_shd = *new Shader("src/objects/Object_color_lit.glsl");
    else if (type == OBJECT_COLOR_UNLIT)
        m_shd = *new Shader("src/objects/Object_color.glsl");
    else
        std::cerr << "Error: Invalid type in object constructor" << std::endl;

    m_shd.bind();
    m_shd.setUniform3f("uColor", clr.x, clr.y, clr.z);

    m_color = clr;
}

Plane::~Plane()
{
    delete &m_model;

    delete &m_vao;
    delete &m_vbo;
    delete &m_ebo;

    delete &m_shd;
    delete &m_tex;
}
