#include "Engien.hpp"
#include "Game/SceneMenu.hpp"
Engien::Engien(const std::string& file_name, std::string main_scene)
{
    init(file_name, main_scene);
}


void Engien::init(const std::string& file_name, std::string main_scene)
{
    m_assets.loadFromFile(file_name);
    m_window.create(sf::VideoMode(500,500),"");
    changeScene(main_scene, std::make_shared<SceneMenu>(this));
}

std::shared_ptr<Scene> Engien::currentScene()
{
    return m_scenes[m_current_scene];
}

Assets& Engien::getAssets()
{
    return m_assets;
}

void Engien::changeScene(const std::string& scene_name, std::shared_ptr<Scene> scene)
{
    m_current_scene = scene_name;
    m_scenes[m_current_scene] = scene;
}

void Engien::run()
{
    while(m_is_running)
    {
        update();
    }
}

void Engien::sEvent()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                m_window.close();
                break;
            }
            case sf::Event::KeyPressed || sf::Event::KeyReleased :
            {
                if(currentScene()->getActionMap().find(event.key.code) != currentScene()->getActionMap().end())
                {
                    const std::string action_type = event.type == sf::Event::KeyPressed ? "START" : "END";
                    //const std::string action_name = currentScene()->getActionMap().at(event.key.code); un comment when doing the map
                    //currentScene()->doAction(Action(action_name, action_type));
                }
            }
        }
    }
}



void Engien::update()
{
    sEvent();
    m_scenes[m_current_scene]->update();
}
