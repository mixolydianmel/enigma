#include "WindowManager.hh"

WindowManager::WindowManager(int width, int height, std::string title) :
    deltaTime(0.f),
    m_windowWidth(width),
    m_windowHeight(height),
    m_title(title),
    m_lastFrame(0.f),
    m_currentFrame(0.f)
{
    if (!glfwInit())
    {
	std::cout << "Error initializing GLFW in WM" << std::endl;
	return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_title.c_str(), NULL, NULL);
    if (!m_window)
    {
	std::cout << "Error creating window in WM" << std::endl;
	glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_lastX = m_windowWidth / 2.f;
    m_lastY = m_windowHeight / 2.f;
}

WindowManager::~WindowManager()
{
    glfwTerminate();
}

bool WindowManager::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

GLFWwindow* WindowManager::getWindow() const
{
    return m_window;
}

void WindowManager::swapBuffers() const
{
    glfwSwapBuffers(m_window);
}

void WindowManager::pollEvents() const
{
    glfwPollEvents();
}

int WindowManager::getWidth() const
{
    return m_windowWidth;
}

int WindowManager::getHeight() const
{
    return m_windowHeight;
}

void WindowManager::processInput()
{
    m_currentFrame = glfwGetTime();
    deltaTime = m_currentFrame - m_lastFrame;
    m_lastFrame = m_currentFrame;

    float cameraSpeed = 1.5f * deltaTime;

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_sceneCamera->setPosition(m_sceneCamera->getPosition() + cameraSpeed * m_sceneCamera->getDirection());
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_sceneCamera->setPosition(m_sceneCamera->getPosition() - cameraSpeed * m_sceneCamera->getDirection());
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_sceneCamera->setPosition(m_sceneCamera->getPosition() + cameraSpeed * m_sceneCamera->getRight());
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_sceneCamera->setPosition(m_sceneCamera->getPosition() - cameraSpeed * m_sceneCamera->getRight());
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_sceneCamera->setPosition(m_sceneCamera->getPosition() + cameraSpeed * glm::vec3(0.f, 1.f, 0.f));
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_sceneCamera->setPosition(m_sceneCamera->getPosition() + cameraSpeed * glm::vec3(0.f, -1.f, 0.f));

    mouseMove();
}

void WindowManager::setWindowManagerSceneCamera(Camera *cam)
{
    m_sceneCamera = cam;
}

void WindowManager::setWindowManagerAspectRatio(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
}

void WindowManager::mouseMove()
{
    glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);

    float xoffset = m_mouseX - m_lastX;
    float yoffset = m_lastY - m_mouseY;
    m_lastX = m_mouseX;
    m_lastY = m_mouseY;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_sceneCamera->setYaw(m_sceneCamera->getYaw() + xoffset);
    m_sceneCamera->setPitch(m_sceneCamera->getPitch() + yoffset);

    if (m_sceneCamera->getPitch() > 89.f)
        m_sceneCamera->setPitch(89.f);
    if (m_sceneCamera->getPitch() < -89.f)
        m_sceneCamera->setPitch(-89.f);

    m_sceneCamera->calculateDirection();
}
