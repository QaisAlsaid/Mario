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
    Assets as;
    as.addTexture("bigsmoke", "Assets/Game/bigsmoke.png");
    auto& tux = as.getTexture("bigsmoke");
    sf::Sprite bigsmoke;
    bigsmoke.setTexture(tux);
    bigsmoke.setPosition(engien->getWindow().getSize().x/2, engien->getWindow().getSize().y/2);
    engien->getWindow().clear(sf::Color::Yellow);
    engien->getWindow().draw(bigsmoke);
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

