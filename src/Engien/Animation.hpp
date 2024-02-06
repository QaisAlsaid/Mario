#pragma once
#include <SFML/Graphics.hpp>
#include "comman/Vec2.hpp"
using namespace kr::math;

class Animation
{
    sf::Sprite sprite;
    size_t      m_frames        = 1; //number of frames for animation
    size_t      m_current_frame = 0; //the current frame being played
    size_t      m_speed         = 0; // speed of transition betwen animation frames
    Vec2        m_size          = {1, 1}; // size of sprite
    std::string m_name          = "default";
public:
    Animation();
    Animation(const std::string& name, const sf::Texture& texture);
    Animation(const std::string& name, const sf::Texture& texture, size_t frame_count, size_t speed){};

    void update();
    bool finished() const;
    const std::string& getName() const;
    const Vec2& getSize() const;
    sf::Sprite& getSprite();
};

