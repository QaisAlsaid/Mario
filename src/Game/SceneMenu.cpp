#include "SceneMenu.hpp"
#include <SFML/Graphics.hpp>


SceneMenu::SceneMenu(Engien* engien)
{
    this->engien = engien;
    init();
}

void SceneMenu::init()
{
    m_view_size = {1280, 720};
    m_view.setSize(m_view_size.toSfVec());
    m_view.setCenter((m_view_size/2).toSfVec());
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
    auto& anim = engien->getAssets().getAnimation("player_walk");
    auto e = entites.addEntity("dummy");
    e->addComponent<CTransform>(Vec2(450, 450), Vec2(1), Vec2(0));
    e->addComponent<CAnimation>(anim, true);
    }
}

void SceneMenu::handelResize(float aspect_ratio)
{
    m_view.setSize(m_view_size.x * aspect_ratio, m_view_size.y * aspect_ratio);
}

void SceneMenu::sRender(const std::shared_ptr<Entity>& e)
{
    engien->getWindow().clear(sf::Color(65,6,56));
    drawGrid();
    //for(auto e : entites.getEntites())
    {
        if(e->hasComponent<CAnimation>() && e->hasComponent<CTransform>())
        {
            e->getComponent<CAnimation>().animation.update(m_delta);
            e->getComponent<CAnimation>().animation.getSprite().setScale(e->getComponent<CTransform>().scale.toSfVec());
            e->getComponent<CAnimation>().animation.getSprite().setPosition(e->getComponent<CTransform>().position.toSfVec());
            engien->getWindow().draw(e->getComponent<CAnimation>().animation.getSprite());
        }
    }
    for(auto& b : m_buttons)
    {
        b.update(engien->getWindow());
        if(b.isPressed(engien->getWindow()))
        {
            if(b.getName() == "Quit")
                engien->quit();
            if(b.getName() == "Play")
                engien->changeScene("Level_1", std::make_shared<SceneGame>(engien));

        }
    }
    engien->getWindow().display();

}

void SceneMenu::drawGrid()
{
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
            {
                srand(time(0));
                sf::RectangleShape r(sf::Vector2f(64, 64));
                r.setOrigin(sf::Vector2f(0, 64));
                r.setPosition(i*64,engien->getWindow().getSize().y - j*64);
                r.setFillColor(sf::Color(rand()*33*i%255,j*66*rand()%255,99*rand()+i+j%255));
                engien->getWindow().draw(r);
            }
    }
}

void SceneMenu::sDoAction(const Action& action)
{
}


void SceneMenu::update(float delta)
{
    m_delta = delta;
    entites.update();
    for(auto& e : entites.getEntites())
        sRender(e);
}

