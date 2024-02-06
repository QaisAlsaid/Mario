#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
class Assets
{
    std::map<std::string, sf::Texture> m_textures;
    //std::map<std::string, > m_sound;
    std::map<std::string, sf::Font> m_fonts;
    std::map<std::string, Animation> m_animations;
public:
    Assets();
    bool findTexture(const std::string& name);
    void loadFromFile(const std::string& file_name);
    void addTexture(const std::string& name, const std::string& path);
    //void addTexture(const std::string& name, const std::string& path);
    void addAnimation(const std::string& name, const Animation& animation);
    void addFont(const std::string& name, const std::string& path);

    sf::Texture& getTexture(const std::string& name);
    //sf::Texture& getTexture(const std::string& name);
    Animation& getAnimation(const std::string& name);
    sf::Font& getFont(const std::string& name);
};
