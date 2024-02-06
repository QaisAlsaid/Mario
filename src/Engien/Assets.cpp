#include "Assets.hpp"
#include <fstream>


Assets::Assets() {}

void Assets::addTexture(const std::string& name, const std::string& path)
{
    sf::Texture texture;
    texture.loadFromFile(path);
    m_textures[name] = texture;
}

void Assets::addFont(const std::string& name, const std::string& path)
{
    sf::Font font;
    font.loadFromFile(path);
    m_fonts[name] = font;
}

void Assets::addAnimation(const std::string& name, const Animation& animation)
{
    m_animations[name] = animation;
}

sf::Texture& Assets::getTexture(const std::string& name)
{
    return m_textures[name];
}

Animation& Assets::getAnimation(const std::string& name)
{
    return m_animations[name];
}

sf::Font& Assets::getFont(const std::string& name)
{
    return m_fonts[name];
}



void Assets::loadFromFile(const std::string& file_name)
{
    std::ifstream file_stream(file_name);
    std::string type;
    while(file_stream >> type)
    {
        if(type != "Animation")
        {
            std::string name, path;
            file_stream >> name >> path;
            if(type == "Texture")
            {
                addTexture(name, path);
            }
            else if(type == "Font")
            {
                addFont(name, path);
            }
            else
            {
                std::cout<<"error, unreconigzed asset type : "<<type<<" "<<name<<" "<<path<<std::endl;
                exit(-1);
            }
        }
        else
        {
            std::string name, texture_name, fps, duration;
            file_stream >> name >> texture_name >> fps >> duration;
            if(m_textures.count(texture_name))
            {
                Animation animation(name, m_textures[texture_name], std::stoi(fps), std::stoi(duration));
            }
            else
            {
                std::cout<<"error, texture : "<<name<<" not found "<<std::endl;
                exit(-1);
            }
        }
    }
}
