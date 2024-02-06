#pragma once
#include "Engien/Scene.hpp"
#include "Engien/Engien.hpp"

class SceneMenu : public Scene
{
public:
    SceneMenu(Engien* engien);
    void sRender()                       override;
    void sDoAction(const Action& action) override;
    void update()                        override;
};

