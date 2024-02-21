#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include <string>
#include "comman/Vec2.hpp"
#include <Actions.hpp>
#include <map>

using namespace kr;



class UIButton
{
    enum class State
    {
        Default = 1,
        Hoverd  = 2,
        Pressed = 3,
    };
public:
    UIButton();
    UIButton(const Vec2& size,const Vec2& position, const std::string& text, const sf::Font& font);
    void update(sf::RenderWindow& window);
    void setText(const std::string& text);
    void setFont(const sf::Font& font);
    void setPosition(const Vec2& position);
    void setSize(const Vec2& size);
    void setTextSize(const int charachter_size);
    void setTextFont(const sf::Font& font);
    void setTextFillColor(const sf::Color& color);
    void setTextOutlineColor(const sf::Color& color);
    void setTextOutlineThickness(float thickness);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    void setOrigin(const Vec2& origin);
    void setOnClickedFillColor(const sf::Color& color);
    void setOnClickedOutlineColor(const sf::Color& color);
    void setOnHoverdFillColor(const sf::Color& color);
    void setOnHoverdOutlineColor(const sf::Color& color);
    bool isHoverd(sf::RenderWindow& window);
    bool isPressed(sf::RenderWindow& window);
    void simulateHover();
    void simulateClick();
    void setName(const std::string& name);
    const std::string& getName() const;
private:
    sf::RectangleShape m_rect;
    State              m_state                     = State::Default;
    std::string        m_name                      = "default";
    sf::Text           m_renderText;
    const Vec2         m_default_button_size       = {50, 50};
    const int          m_default_text_size         = 16;
    const sf::Color    m_default_button_fill_color = sf::Color(78, 78, 78);
    const sf::Color    m_default_text_fill_color   = sf::Color(255, 255, 255);
    std::map<std::string, sf::Color> m_color_map;
    sf::FloatRect m_textRect;


private:
    void centerText();
    void updateColor();
    std::pair<sf::RectangleShape, sf::Text> getElements();

};
