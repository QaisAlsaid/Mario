#pragma once
#include "Engien/Scene.hpp"
#include "Engien.hpp"
#include "UIButton.hpp"
class SceneGame : public Scene
{
public:
    short r=0,g=0,bb=0;
    SceneGame(Engien* engien) {this->engien = engien;}
    void sRender()
    {
        srand(time(0));
        r += rand()%3; g+= rand()%5; bb += rand()%1;if(r>=255 ||g>=255||bb>=255) r = g = bb = 0;
        auto& font = engien->getAssets().getFont("font");
        UIButton b(Vec2(200),Vec2(250),"Back to Menu",font);
        b.setOnHoverdFillColor(sf::Color(68,32,0));
        if(b.isClicked(engien->getWindow())) engien->changeScene("menu",engien->getScene("menu"));
        b.isHoverd(engien->getWindow());
        engien->getWindow().clear(sf::Color(r,g,bb));
        engien->getWindow().draw(b.getElements().first);
        engien->getWindow().draw(b.getElements().second);
        engien->getWindow().display();
        auto e = entites.addEntity("dummy");
        e->addComponent<CTransform>(Vec2(100),Vec2(2),Vec2(2));
        auto t = e->hasComponent<CTransform>();
        std::cout<<t<<std::endl;
    }
    void sDoAction(const Action& action) {}
    void update() {sRender();}
};
