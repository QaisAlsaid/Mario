#pragma once
#include "Engien/Scene.hpp"
#include "Engien/Engien.hpp"
#include "Game/SceneGame.hpp"
#include "UIButton.hpp"
class SceneMenu : public Scene
{
public:
    SceneMenu(Engien* engien);
    void update() override;

private:
    std::vector<UIButton> m_buttons;
    void init();
    void sRender()                       override;
    void sDoAction(const Action& action) override;
};

