#include "Renderer.hh"

Renderer::Renderer()
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
	std::cout << "Error initializing renderer." << std::endl;
	std::cout << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Renderer::setClearColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& vao, const ElementBuffer& ebo, const Shader& shd) const
{
    shd.bind();
    vao.bind();
    ebo.bind();

    glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(Object* obj)
{
    obj->bindAll();
    obj->setShaderMVP(obj->getModelMatrix(),
            m_sceneCamera->getViewMatrix(),
            glm::perspective(glm::radians(m_sceneCamera->getFOV()), m_aspectRatio, 0.1f, 100.f));

    glDrawElements(GL_TRIANGLES, obj->getEBO().getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::setRendererSceneCamera(Camera *cam)
{
    m_sceneCamera = cam;
}

void Renderer::setRendererAspectRatio(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
}
