#include "Manager.hh"

Manager::Manager(Renderer& rnd, WindowManager& wm) :
    m_renderer(rnd),
    m_windowManager(wm)
{
    glfwSetFramebufferSizeCallback(m_windowManager.getWindow(), Manager::framebuffer_size_callback);
}

void Manager::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Manager::setSceneCamera(Camera* cam)
{
    m_renderer.setRendererSceneCamera(cam);
    m_windowManager.setWindowManagerSceneCamera(cam);
}

void Manager::setAspectRatio(const float aspectRatio)
{
    m_renderer.setRendererAspectRatio(aspectRatio);
    m_windowManager.setWindowManagerAspectRatio(aspectRatio);
}
