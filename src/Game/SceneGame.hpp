#pragma once
#include "Engien/Scene.hpp"
#include "Engien.hpp"
#include "UIButton.hpp"
class SceneGame : public Scene
{
public:
    SceneGame(Engien* engien) {this->engien = engien;}
    void sRender()
    {
        auto& font = engien->getAssets().getFont("font");
        UIButton b(Vec2(200),Vec2(250),"Back to Menu",font);
        engien->getWindow().clear(sf::Color(245,78,9));
        engien->getWindow().draw(b.getElements().first);
        engien->getWindow().draw(b.getElements().second);
        if(b.isClicked(engien->getWindow())) engien->changeScene("menu",engien->getScene("menu"));
        engien->getWindow().display();
    }
    void sDoAction(const Action& action) {}
    void update() {sRender();}
};
