#include "Manager.hh"
#include "objects/Cube.hh"
#include "objects/Plane.hh"

int main(void)
{
    WindowManager wm(1280, 720, "OpenGL");

    Renderer rnd;
    rnd.setClearColor(0.2f, 0.2f, 0.3f);

    Manager m(rnd, wm);

    Camera* cam = new Camera(glm::vec3(0.f, 0.f, 3.f), 60.f);

    m.setSceneCamera(cam);
    m.setAspectRatio(1.f * wm.getWidth() / wm.getHeight());

    Cube* lightSource = new Cube(OBJECT_COLOR_UNLIT, glm::vec3(1.f, 1.f, 1.f));
    lightSource->translate({0.75f, 1.f, 1.5f});
    lightSource->scale({0.1f, 0.1f, 0.1f});

    Cube* cb = new Cube(OBJECT_COLOR_LIT, glm::vec3(1.f, 0.3f, 0.3f));

    cb->bindAll();
    cb->getSHD().setUniform3f("lightColor", lightSource->getColor());
    cb->getSHD().setUniform3f("lightPos", lightSource->getPosition());
    cb->getSHD().setUniform3f("viewPos", cam->getPosition());

    Plane* pl = new Plane(OBJECT_COLOR_LIT, glm::vec3(0.25f, 0.25f, 0.25f));
    pl->translate({0.f, -0.75f, 0.f});
    pl->rotate({-90.f, 1.f, 0.f, 0.f});
    pl->scale({10.f, 10.f, 1.f});

    pl->bindAll();
    pl->getSHD().setUniform3f("lightColor", lightSource->getColor());
    pl->getSHD().setUniform3f("lightPos", lightSource->getPosition());
    pl->getSHD().setUniform3f("viewPos", cam->getPosition());

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
