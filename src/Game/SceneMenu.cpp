#include "SceneMenu.hpp"
#include <SFML/Graphics.hpp>

SceneMenu::SceneMenu(Engien* engien)
{
    this->engien = engien;
    init();
}

void SceneMenu::init()
{
    regesterAction(sf::Keyboard::A, "Test");
}


void SceneMenu::sRender()
{
    std::string name = "big_smoke_idel";
    auto& anim = engien->getAssets().getAnimation(name);
    engien->getWindow().clear(sf::Color::Yellow);
    anim.getSprite().setPosition(250,250);
    engien->getWindow().draw(anim.getSprite());
    engien->getWindow().display();

}


void SceneMenu::sDoAction(const Action& action)
{
    if(action.name() == "Test")
        engien->quit();
}


void SceneMenu::update()
{

    sRender();
}

