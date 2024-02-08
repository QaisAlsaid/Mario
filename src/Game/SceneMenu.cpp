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
    auto& font = engien->getAssets().getFont("font");
    for(int i = 0; i < 3; i++)
    {
        std::string text;
        if(i == 0) text = "Play";if(i == 1) text = "Options"; if(i == 2) text = "Quit";
        UIButton b(Vec2(100), Vec2(50, 130 * (i+1)), text, font);
        b.setOutlineThickness(7);
        b.setOutlineColor(sf::Color::Black);
        b.setOnClickedFillColor(sf::Color::Red);
        b.setOnClickedOutlineColor(sf::Color::Black);
        b.setOnHoverdFillColor(sf::Color(0,0,140));
        b.setOnHoverdOutlineColor(sf::Color::Black);
        b.setName(text);
        m_buttons.push_back(b);

    }
}


void SceneMenu::sRender()
{
    auto& anim = engien->getAssets().getAnimation("big_smoke_idel");
    engien->getWindow().clear(sf::Color(65,6,56));
    anim.getSprite().setPosition(250,250);
    engien->getWindow().draw(anim.getSprite());
    for(auto& b : m_buttons)
    {
        b.isHoverd(engien->getWindow());
        engien->getWindow().draw(b.getElements().first);
        engien->getWindow().draw(b.getElements().second);
        if(b.isClicked(engien->getWindow()))
        {
            if(b.getName() == "Quit")
                engien->quit();
            if(b.getName() == "Play")
                engien->changeScene("dummy", std::make_shared<SceneGame>(engien));
        }
    }
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

