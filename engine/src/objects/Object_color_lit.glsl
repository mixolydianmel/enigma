#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    FragPos = vec3(uModel * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(uModel))) * aNormal;
}

#shader fragment
#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float metallic;
};

uniform Material material;

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight pointLight;

vec3 PointLightCalc(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 ambient = light.ambient * material.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diffuseStrength * material.diffuse);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.metallic * 128);
    vec3 specular = light.specular * (material.specular * spec);

    return (ambient + diffuse + specular);
}

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = PointLightCalc(pointLight, Normal, FragPos, viewDir);
    FragColor = vec4(result, 1.0);
}
