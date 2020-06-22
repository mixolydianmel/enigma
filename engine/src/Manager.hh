#ifndef MANAGER_H
#define MANAGER_H

#include "Renderer.hh"
#include "WindowManager.hh"

class Manager
{
    public:
        Manager(Renderer& rnd, WindowManager& wm);

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        void setSceneCamera(Camera* cam);
        void setAspectRatio(float aspectRatio);
    private:
        Renderer& m_renderer;
        WindowManager& m_windowManager;
};

#endif
