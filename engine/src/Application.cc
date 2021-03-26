#include "Manager.hh"
#include "objects/Cube.hh"
#include "objects/Plane.hh"
#include <cstdint>
#include <cstdio>

int main(void)
{
    // GLFW handler
    WindowManager wm(2560, 1440, "OpenGL");

    // GL handler
    Renderer rnd;
    rnd.setClearColor(0.1568f, 0.1647f, 0.2117f);

    // Communicator and game manager
    Manager m(rnd, wm);

    // Camera
    Camera* cam = new Camera(glm::vec3(0.f, 0.f, 3.f), 60.f);

    // Set scene variables
    m.setSceneCamera(cam);
    m.setAspectRatio(1.f * wm.getWidth() / wm.getHeight());

    // Make a light source
    Cube* lightSource = new Cube(OBJECT_COLOR_UNLIT, glm::vec3(1.0f, 1.0f, 1.0f));
    lightSource->translate({0.75f, 1.f, 1.5f});
    lightSource->scale({0.1f, 0.1f, 0.1f});

    // Make a cube
    Cube* cb = new Cube(OBJECT_COLOR_LIT, glm::vec3(1.f, 0.3f, 0.3f));

    // Set cube lighting uniforms
    cb->bindAll();
    cb->getSHD().setUniform3f("pointLight.ambient", lightSource->getColor() * 0.2f);
    cb->getSHD().setUniform3f("pointLight.diffuse", lightSource->getColor() * 0.5f);
    cb->getSHD().setUniform3f("pointLight.specular", lightSource->getColor());
    cb->getSHD().setUniform3f("pointLight.position", lightSource->getPosition());
    cb->getSHD().setUniform3f("viewPos", cam->getPosition());

    // Set cube material uniforms
    cb->getSHD().setUniform3f("material.ambient", 0.1745f, 0.01175f, 0.01175f);
    cb->getSHD().setUniform3f("material.diffuse", 0.61424f, 0.04136f, 0.04136f);
    cb->getSHD().setUniform3f("material.specular", 0.727811f, 0.62959f, 0.62959f);
    cb->getSHD().setUniform1f("material.metallic", 0.6f);

    // Make a plane
    Plane* pl = new Plane(OBJECT_COLOR_LIT, glm::vec3(0.8f, 0.8f, 0.8f));
    pl->translate({0.f, -0.75f, 0.f});
    pl->rotate({-90.f, 1.f, 0.f, 0.f});
    pl->scale({10.f, 10.f, 1.f});

    // Set plane lighting uniforms
    pl->bindAll();
    pl->getSHD().setUniform3f("pointLight.ambient", lightSource->getColor() * 0.2f);
    pl->getSHD().setUniform3f("pointLight.diffuse", lightSource->getColor() * 0.5f);
    pl->getSHD().setUniform3f("pointLight.specular", lightSource->getColor());
    pl->getSHD().setUniform3f("pointLight.position", lightSource->getPosition());
    pl->getSHD().setUniform3f("viewPos", cam->getPosition());

    // Set plane material uniforms
    pl->getSHD().setUniform3f("material.ambient", 0.05f, 0.05f, 0.05f);
    pl->getSHD().setUniform3f("material.diffuse", 0.5f, 0.5f, 0.5f);
    pl->getSHD().setUniform3f("material.specular", 0.7f, 0.7f, 0.7f);
    pl->getSHD().setUniform1f("material.metallic", 0.078125f);

    while (!wm.shouldClose())
    {
	wm.processInput();

	rnd.clear();

        cb->bindAll();
        cb->getSHD().setUniform3f("viewPos", cam->getPosition());

        pl->bindAll();
        pl->getSHD().setUniform3f("viewPos", cam->getPosition());

        rnd.draw(cb);
        rnd.draw(lightSource);
        rnd.draw(pl);

	wm.swapBuffers();
	wm.pollEvents();
    }
}
