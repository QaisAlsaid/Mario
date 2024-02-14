#pragma once
#include "Engien/Scene.hpp"
#include "Engien/Engien.hpp"
#include "Game/SceneGame.hpp"
#include "UIButton.hpp"
class SceneMenu : public Scene
{
public:
    SceneMenu(Engien* engien);
    void update(float delta) override;
    void handelResize(float aspect_ratio) override;
private:
    void init();
    void drawGrid();
    std::vector<UIButton> m_buttons;
    void sRender()                       override;
    void sDoAction(const Action& action) override;
private:
    sf::View m_view;
    Vec2     m_view_size = {1280, 720};
};

