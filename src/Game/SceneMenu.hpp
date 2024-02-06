#pragma once
#include "Engien/Scene.hpp"
#include "Engien/Engien.hpp"

class SceneMenu : public Scene
{
public:
    SceneMenu(Engien* engien);
    void update() override;

private:
    void init();
    void sRender()                       override;
    void sDoAction(const Action& action) override;
};

