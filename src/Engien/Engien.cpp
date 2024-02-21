#include "Engien.hpp"
#include "Game/SceneMenu.hpp"
Engien::Engien(const std::string& file_name, std::string main_scene)
{
    init(file_name, main_scene);
}


void Engien::init(const std::string& file_name, std::string main_scene)
{
    m_assets.loadFromFile(file_name);
    m_window.create(sf::VideoMode(1280,720),"");
    //m_window.setKeyRepeatEnabled(false);
    m_window.setFramerateLimit(90);
    changeScene(main_scene, std::make_shared<SceneMenu>(this));
}

std::shared_ptr<Scene> Engien::currentScene()
{
    return m_scenes[m_current_scene];

}

std::shared_ptr<Scene> Engien::getScene(const std::string& name)
{
    auto iter = m_scenes.find(name);
    if(iter != m_scenes.end()) {return iter->second;}
}

void Engien::quit()
{
    m_is_running = false;
    m_window.close();
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

void Engien::handelResize()
{
    currentScene()->handelResize(m_window.getSize().x/m_window.getSize().y);
}

void Engien::sEvent()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            quit();
        }
        if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            sUserInput(event);
        }
        if(event.type == sf::Event::Resized)
        {
            handelResize();
        }
    }
}


void Engien::sUserInput(const sf::Event& event)
{
        auto iter = currentScene()->getActionMap().find(event.key.code);
        if(iter != currentScene()->getActionMap().end())
        {
            const std::string action_type = event.type == sf::Event::KeyPressed ? "START" : "END";
            const std::string& action_name = currentScene()->getActionMap().at(event.key.code);
            currentScene()->doAction(Action(action_name, action_type));
        }
}

short Engien::getFps() const
{
    return m_fps;
}

void Engien::update()
{
    m_delta = m_clock.restart().asSeconds();
    m_fps = (1.f / m_delta - m_last_delta) + 1;
    m_last_delta = m_delta;
    std::cout<<m_fps<<std::endl;
    sEvent();
    currentScene()->update(m_delta);
}

