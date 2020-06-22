#include "Cube.hh"
#include <iostream>

Cube::Cube(unsigned int type, const std::string& tex,
        glm::vec3 pos, glm::vec4 rot, glm::vec3 scl)
{
    m_model = *new glm::mat4(1.f);

    m_position = pos;
    m_rotation = rot;
    m_scale = scl;

    m_vertices = {
         0.5f, -0.5f, -0.5f, 0.f, 0.f,  0.f,  0.f, -1.f, // back
        -0.5f, -0.5f, -0.5f, 1.f, 0.f,  0.f,  0.f, -1.f,
        -0.5f,  0.5f, -0.5f, 1.f, 1.f,  0.f,  0.f, -1.f,
         0.5f,  0.5f, -0.5f, 0.f, 1.f,  0.f,  0.f, -1.f,

        -0.5f, -0.5f,  0.5f, 0.f, 0.f,  0.f,  0.f,  1.f, // front
         0.5f, -0.5f,  0.5f, 1.f, 0.f,  0.f,  0.f,  1.f,
         0.5f,  0.5f,  0.5f, 1.f, 1.f,  0.f,  0.f,  1.f,
        -0.5f,  0.5f,  0.5f, 0.f, 1.f,  0.f,  0.f,  1.f,

        -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f,  0.f,  0.f, // left
        -0.5f, -0.5f,  0.5f, 1.f, 0.f, -1.f,  0.f,  0.f,
        -0.5f,  0.5f,  0.5f, 1.f, 1.f, -1.f,  0.f,  0.f,
        -0.5f,  0.5f, -0.5f, 0.f, 1.f, -1.f,  0.f,  0.f,

         0.5f, -0.5f,  0.5f, 0.f, 0.f,  1.f,  0.f,  0.f, // right
         0.5f, -0.5f, -0.5f, 1.f, 0.f,  1.f,  0.f,  0.f,
         0.5f,  0.5f, -0.5f, 1.f, 1.f,  1.f,  0.f,  0.f,
         0.5f,  0.5f,  0.5f, 0.f, 1.f,  1.f,  0.f,  0.f,

        -0.5f,  0.5f,  0.5f, 0.f, 0.f,  0.f,  1.f,  0.f, // top
         0.5f,  0.5f,  0.5f, 1.f, 0.f,  0.f,  1.f,  0.f,
         0.5f,  0.5f, -0.5f, 1.f, 1.f,  0.f,  1.f,  0.f,
        -0.5f,  0.5f, -0.5f, 0.f, 1.f,  0.f,  1.f,  0.f,

        -0.5f, -0.5f, -0.5f, 0.f, 0.f,  0.f, -1.f,  0.f, // bottom
         0.5f, -0.5f, -0.5f, 1.f, 0.f,  0.f, -1.f,  0.f,
         0.5f, -0.5f,  0.5f, 1.f, 1.f,  0.f, -1.f,  0.f,
        -0.5f, -0.5f,  0.5f, 0.f, 1.f,  0.f, -1.f,  0.f
    };

    m_indices = {
        0, 1, 2, // back
        2, 3, 0,

        4, 5, 6, // front
        6, 7, 4,

        8, 9, 10, // left
        10, 11, 8,

        12, 13, 14, // right
        14, 15, 12,

        16, 17, 18, // top
        18, 19, 16,

        20, 21, 22, // bottom
        22, 23, 20
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

Cube::Cube(unsigned int type, const glm::vec3& clr,
        glm::vec3 pos, glm::vec4 rot, glm::vec3 scl)
{
    m_model = *new glm::mat4(1.f);

    m_position = pos;
    m_rotation = rot;
    m_scale = scl;

    m_vertices = {
         0.5f, -0.5f, -0.5f, 0.f, 0.f,  0.f,  0.f, -1.f,
        -0.5f, -0.5f, -0.5f, 1.f, 0.f,  0.f,  0.f, -1.f,
        -0.5f,  0.5f, -0.5f, 1.f, 1.f,  0.f,  0.f, -1.f,
         0.5f,  0.5f, -0.5f, 0.f, 1.f,  0.f,  0.f, -1.f,

        -0.5f, -0.5f,  0.5f, 0.f, 0.f,  0.f,  0.f,  1.f,
         0.5f, -0.5f,  0.5f, 1.f, 0.f,  0.f,  0.f,  1.f,
         0.5f,  0.5f,  0.5f, 1.f, 1.f,  0.f,  0.f,  1.f,
        -0.5f,  0.5f,  0.5f, 0.f, 1.f,  0.f,  0.f,  1.f,

        -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f,  0.f,  0.f,
        -0.5f, -0.5f,  0.5f, 1.f, 0.f, -1.f,  0.f,  0.f,
        -0.5f,  0.5f,  0.5f, 1.f, 1.f, -1.f,  0.f,  0.f,
        -0.5f,  0.5f, -0.5f, 0.f, 1.f, -1.f,  0.f,  0.f,

         0.5f, -0.5f,  0.5f, 0.f, 0.f,  1.f,  0.f,  0.f,
         0.5f, -0.5f, -0.5f, 1.f, 0.f,  1.f,  0.f,  0.f,
         0.5f,  0.5f, -0.5f, 1.f, 1.f,  1.f,  0.f,  0.f,
         0.5f,  0.5f,  0.5f, 0.f, 1.f,  1.f,  0.f,  0.f,

        -0.5f,  0.5f,  0.5f, 0.f, 0.f,  0.f,  1.f,  0.f,
         0.5f,  0.5f,  0.5f, 1.f, 0.f,  0.f,  1.f,  0.f,
         0.5f,  0.5f, -0.5f, 1.f, 1.f,  0.f,  1.f,  0.f,
        -0.5f,  0.5f, -0.5f, 0.f, 1.f,  0.f,  1.f,  0.f,

        -0.5f, -0.5f, -0.5f, 0.f, 0.f,  0.f, -1.f,  0.f,
         0.5f, -0.5f, -0.5f, 1.f, 0.f,  0.f, -1.f,  0.f,
         0.5f, -0.5f,  0.5f, 1.f, 1.f,  0.f, -1.f,  0.f,
        -0.5f, -0.5f,  0.5f, 0.f, 1.f,  0.f, -1.f,  0.f
    };

    m_indices = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
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

Cube::~Cube()
{
    delete &m_model;

    delete &m_vao;
    delete &m_vbo;
    delete &m_ebo;

    delete &m_shd;
    delete &m_tex;
}
