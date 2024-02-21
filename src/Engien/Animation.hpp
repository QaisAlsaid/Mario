#pragma once
#include <SFML/Graphics.hpp>
#include "comman/Vec2.hpp"
using namespace kr;

class Animation
{
    float       m_time          = 0;
    size_t      m_frames        = 1; //  number of frames for animation
    size_t      m_current_frame = 0; //  the current frame being played
    float       m_speed         = 0; // speed of transition betwen animation frames in seconds
    Vec2        m_size          = {1, 1}; // size of sprite
    std::string m_name          = "default";
    bool        m_repeated      = true;
    bool        m_cycle         = 1;
    bool        m_reverse_cycle = false;
    bool        m_is_finished   = false;
    bool        m_right         = true;
    sf::Sprite  m_sprite;
public:
    Animation();
    Animation(const std::string& name, const sf::Texture& texture);
    Animation(const std::string& name, const sf::Texture& texture, size_t frame_count, float speed);
    void setRepeatedCycle(bool repeated);
    void setRepeated(bool repeated);
    void isRepeated();
    void update(float delta);
    bool finished() const;
    const std::string& name() const;
    const Vec2& size() const;
    bool isRight() const;
    void setRight(bool right);
    sf::Sprite& getSprite();
};

