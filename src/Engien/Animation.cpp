#include "Animation.hpp"

Animation::Animation(){}

Animation::Animation(const std::string& name, const sf::Texture& texture)
{
    m_size = {texture.getSize().x, texture.getSize().y};
    m_sprite.setTexture(texture);
    m_name = name;
}
// TODO : when you have an animation texture with more than one row make the frame count a Vec2
Animation::Animation(const std::string& name, const sf::Texture& texture, size_t frame_count, float speed)
{
    m_size = {texture.getSize().x / frame_count, texture.getSize().y};
    m_name = name;
    m_frames = frame_count;
    m_speed = speed;
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
}


const Vec2& Animation::size() const
{
    return m_size;
}

const std::string& Animation::name() const
{
    return m_name;
}

void Animation::setRepeated(bool repeated)
{
    m_repeated = repeated;
}

void Animation::setRepeatedCycle(bool repeated)
{
    m_cycle = true;
    m_repeated = true;
}

bool Animation::finished() const
{
    return m_is_finished;
}

sf::Sprite& Animation::getSprite()
{
    return m_sprite;
}

bool Animation::isRight() const
{
    return m_right;
}

void Animation::setRight(bool right)
{
    m_right = right;
}

void Animation::update(float delta)
{
    if(!m_is_finished)
    {
        m_time += delta;
        if(m_time >= m_speed * m_current_frame)
        {
            if(m_right)
            m_sprite.setTextureRect(sf::IntRect(m_size.x * (m_current_frame), 0 ,m_size.x, m_size.y));
            else
                m_sprite.setTextureRect(sf::IntRect(m_size.x * (m_current_frame + 1), 0 ,-abs(m_size.x), m_size.y));

            m_current_frame ++;
        }
        if(m_time >= m_speed * (m_frames-1))
        {
            if(m_repeated)
            {
                m_current_frame = 0;
                m_time = 0;
            }
            else
            {
                m_is_finished = true;
                m_sprite.setTextureRect(sf::IntRect(m_size.x * (m_frames - 1), 0 ,m_size.x, m_size.y));
            }
        }
    }
}


