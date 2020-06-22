#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

class Shader
{
    public:
        Shader(const std::string& filepath);
        ~Shader();

        void bind() const;
        void unbind() const;

        void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void setUniform3f(const std::string& name, float v0, float v1, float v2);
        void setUniform3f(const std::string& name, const glm::vec3& v);
        void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
        void setUniform1f(const std::string& name, float value);
        void setUniform1i(const std::string& name, int value);
    private:
        unsigned int m_rendererID;
        std::string m_filepath;

        std::unordered_map<std::string, int> m_uniformLocationCache;

        unsigned int createShader(const std::string& filepath);

        unsigned int getUniformLocation(const std::string& name);
};

#endif
