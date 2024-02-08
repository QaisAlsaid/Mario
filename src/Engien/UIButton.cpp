#include "UIButton.hpp"


UIButton::UIButton()
{
    setSize(m_default_button_size);
    setFillColor(m_default_button_fill_color);
    m_color_map["b_d_f_c"] = m_default_button_fill_color;
    setTextFillColor(m_default_text_fill_color);
    setTextSize(m_default_text_size);
}


UIButton::UIButton(const Vec2& size,const Vec2& position, const std::string& text, const sf::Font& font)
{
    setFont(font);
    setText(text);
    setTextSize(m_default_text_size);
    setSize(size);
    setPosition(position);
    setFillColor(m_default_button_fill_color);
    m_color_map["b_d_f_c"] = m_default_button_fill_color;
    setTextFillColor(m_default_text_fill_color);
}


void UIButton::setText(const std::string& text)
{
    m_renderText.setString(text);
}



void UIButton::setTextSize(const int charachter_size)
{
    m_renderText.setCharacterSize(charachter_size);
    centerText();
}


void UIButton::setSize(const Vec2& size)
{
    m_rect.setOrigin((size/2).toSfVec());
    m_rect.setSize(size.toSfVec());
    centerText();
}


void UIButton::setPosition(const Vec2& position)
{
    m_rect.setPosition(position.toSfVec());
    centerText();
}


void UIButton::setFillColor(const sf::Color& color)
{
    m_color_map["b_d_f_c"] = color;
    m_rect.setFillColor(color);
}


void UIButton::setOutlineColor(const sf::Color& color)
{
    m_color_map["b_d_o_c"] = color;
    m_rect.setOutlineColor(color);
}


void UIButton::setOutlineThickness(float thickness)
{
    m_rect.setOutlineThickness(thickness);
}



void UIButton::setTextFillColor(const sf::Color& color)
{
    m_renderText.setFillColor(color);
}


void UIButton::setTextOutlineColor(const sf::Color& color)
{
    m_renderText.setOutlineColor(color);
}


void UIButton::setTextOutlineThickness(float thickness)
{
    m_renderText.setOutlineThickness(thickness);
}


void UIButton::setFont(const sf::Font& font)
{
    m_renderText.setFont(font);
}


std::pair<sf::RectangleShape, sf::Text> UIButton::getElements()
{
    return std::pair<sf::RectangleShape, sf::Text>(m_rect, m_renderText);
}


void UIButton::setOnClickedFillColor(const sf::Color& color)
{
    m_color_map["b_c_f_c"] = color;
}


void UIButton::setOnClickedOutlineColor(const sf::Color& color)
{
    m_color_map["b_c_o_c"] = color;
}


void UIButton::setOnHoverdFillColor(const sf::Color& color)
{
    m_color_map["b_h_f_c"] = color;
}


void UIButton::setOnHoverdOutlineColor(const sf::Color& color)
{
    m_color_map["b_h_o_c"] = color;
}


bool UIButton::isHoverd(sf::RenderWindow& window)
{
    if(sf::Mouse::getPosition(window).x > m_rect.getPosition().x - m_rect.getSize().x / 2.f && sf::Mouse::getPosition(window).x < m_rect.getPosition().x + m_rect.getSize().x / 2.f
       && sf::Mouse::getPosition(window).y < m_rect.getPosition().y + m_rect.getSize().y / 2.f && sf::Mouse::getPosition(window).y > m_rect.getPosition().y - m_rect.getSize().y / 2.f)
    {
        m_rect.setFillColor(m_color_map["b_h_f_c"]);
        m_rect.setOutlineColor(m_color_map["b_h_o_c"]);
        return true;
    }
    m_rect.setFillColor(m_color_map["b_d_f_c"]);
    m_rect.setOutlineColor(m_color_map["b_d_o_c"]);
    return false;
}


void UIButton::setName(const std::string& name)
{
    m_name = name;
}


const std::string& UIButton::getName() const
{
    return m_name;
}


bool UIButton::isClicked(sf::RenderWindow& window)
{
    if(sf::Mouse::getPosition(window).x > m_rect.getPosition().x - m_rect.getSize().x / 2.f && sf::Mouse::getPosition(window).x < m_rect.getPosition().x + m_rect.getSize().x / 2.f
       && sf::Mouse::getPosition(window).y < m_rect.getPosition().y + m_rect.getSize().y / 2.f && sf::Mouse::getPosition(window).y > m_rect.getPosition().y - m_rect.getSize().y / 2.f
       && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_rect.setFillColor(m_color_map["b_c_f_c"]);
        m_rect.setOutlineColor(m_color_map["b_c_o_c"]);
        return true;
    }
    m_rect.setFillColor(m_color_map["b_d_f_c"]);
    m_rect.setOutlineColor(m_color_map["b_d_o_c"]);
    return false;
}


void UIButton::centerText()
{
    sf::FloatRect textRect = m_renderText.getLocalBounds();
    m_renderText.setOrigin(textRect.left + textRect.width/2.f,
               textRect.top  + textRect.height/2.f);
    m_renderText.setPosition(m_rect.getPosition());
}
