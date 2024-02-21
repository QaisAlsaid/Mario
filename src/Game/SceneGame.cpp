#include "SceneGame.hpp"

#include "Phisics.hpp"

SceneGame::SceneGame(Engien* engien)
{
    this->engien = engien;
    init();
}

void SceneGame::init()
{
    loadLevel("Assets/Game/Levels/test.txt");
    regesterAction(sf::Keyboard::D, "DRight");
    regesterAction(sf::Keyboard::A, "DLeft");
    regesterAction(sf::Keyboard::Space, "DUp");
    regesterAction(sf::Keyboard::S, "DDown");
    regesterAction(sf::Keyboard::B, "BoundingBox");
    regesterAction(sf::Keyboard::G, "Grid");
    regesterAction(sf::Keyboard::T, "Tux");
    regesterAction(sf::Keyboard::F, "Fps");
    regesterAction(sf::Keyboard::W, "Shoot");
    regesterAction(sf::Keyboard::R, "restart");
    m_view = sf::View(sf::FloatRect(0 ,0 ,
    engien->getWindow().getSize().x, engien->getWindow().getSize().y));
    m_text.setFont(engien->getAssets().getFont("font"));
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(24);
    m_text.setOutlineThickness(5);
    spawnPlayer();
}

void SceneGame::loadLevel(const std::string& path)
{
    entites = EntityManager();//restart EntityManager every level load
    std::ifstream file_buffer(path);
    std::string type;
    while(file_buffer >> type)
    {
        std::string name;
        unsigned int Gx, Gy;
        if(type == "Dec")
        {
            file_buffer >> name >> Gx >> Gy;
            auto e = entites.addEntity("Dec");
            auto& anim = engien->getAssets().getAnimation(name);
            e->addComponent<CAnimation>(anim, true);
            e->addComponent<CTransform>(gridToPixel(Vec2(Gx, Gy), e));
        }
        else if(type == "Camera")
        {
            Vec2 center,view_port;
            file_buffer >> center.x >> center.y >> view_port.x >> view_port.y;
            m_view.setCenter(center.toSfVec());
            m_view.setSize(view_port.toSfVec());
        }
        else if(type == "Tile")
        {
            float Cw,Ch;
            file_buffer >> name >> Gx >> Gy >> Cw >> Ch;
            auto e = entites.addEntity(name == "qblock" ? "qblock" : "Tile");
            if(name == "qblock")
                e->addComponent<CState>("untouched");
            else e->addComponent<CState>("default");
            auto& anim = engien->getAssets().getAnimation(name);
            e->addComponent<CAnimation>(anim, true);
            e->addComponent<CTransform>(gridToPixel(Vec2(Gx, Gy), e));
            e->addComponent<CBoundingBox>(Vec2(Cw, Ch));
        }
        else if(type == "Player")
        {
            file_buffer >> m_player_config.Gx >> m_player_config.Gy >> m_player_config.Cw >> m_player_config.Ch;
            file_buffer >> m_player_config.S >> m_player_config.Ms >> m_player_config.Js >> m_player_config.anim;
        }
        else if(type == "TileB")
        {
            float Cw,Ch;
            file_buffer >> name >> Cw >> Ch >> Gx >> Gy;
            auto e = entites.addEntity(type);
            e->addComponent<CTransform>(Vec2(0), Vec2(1),Vec2(0));
            auto& anim = engien->getAssets().getAnimation(name);
            e->addComponent<CAnimation>(anim, true);
            e->addComponent<CBoundingBox>(Vec2(Cw, Ch));
            e->getComponent<CTransform>().position = gridToPixel(Vec2(Gx, Gy),e);
            e->addComponent<CState>("default");
            e->getComponent<CAnimation>().animation.getSprite().setColor(sf::Color(140,140,140));
        }
        else if(type.at(0) == '_')
        {
            type = type.substr(1, type.size());
        }
        else if(type == "repeat")
        {
            std::string dummyx,dummyy;
            int start, finsh;
            float Cw,Ch;
            file_buffer >> dummyx >> start >> finsh;
            file_buffer >> type;
            for(int i = start; i < finsh; i++)
            {
                if(type == "Dec")
                {
                    if(i == start)
                        file_buffer >> name >> Gx >> dummyx >> Gy >> dummyy;
                    auto e = entites.addEntity(type);
                    auto& anim = engien->getAssets().getAnimation(name);
                    e->addComponent<CAnimation>(anim, true);
                    e->addComponent<CTransform>(gridToPixel(Vec2(Gx * (dummyx == "i" ? i : 1), Gy * (dummyy == "i" ? i : 1)),e));
                }
                else if(type == "Tile")
                {
                    if(i == start)
                    {
                        file_buffer >> name >> Gx >> dummyx >> Gy >> dummyy >> Cw >> Ch;
                    }
                    auto e = entites.addEntity(type);
                    e->addComponent<CTransform>(Vec2(0), Vec2(1),Vec2(0));
                    auto& anim = engien->getAssets().getAnimation(name);
                    e->addComponent<CAnimation>(anim, true);
                    e->addComponent<CBoundingBox>(Vec2(Cw, Ch));
                    e->getComponent<CTransform>().position = gridToPixel(Vec2(Gx * (dummyx == "i" ? i : 1), Gy * (dummyy == "i" ? i : 1)),e);
                    if(Gy == 0) e->getComponent<CAnimation>().animation.getSprite().setColor(sf::Color(140,140,140));
                }
                else if(type == "TileB")
                {
                    if(i == start)
                    {
                        file_buffer >> name >> Gx >> dummyx >> Gy >> dummyy >> Cw >> Ch;
                    }
                    auto e = entites.addEntity(type);
                    e->addComponent<CTransform>(Vec2(0), Vec2(1),Vec2(0));
                    auto& anim = engien->getAssets().getAnimation(name);
                    e->addComponent<CAnimation>(anim, true);
                    e->addComponent<CBoundingBox>(Vec2(Cw, Ch));
                    e->getComponent<CTransform>().position = gridToPixel(Vec2(Gx * (dummyx == "i" ? i : 1), Gy * (dummyy == "i" ? i : 1)),e);
                    e->addComponent<CState>("default");
                    e->getComponent<CAnimation>().animation.getSprite().setColor(sf::Color(140,140,140));
                }
                else if(type == "Player")
                {
                    std::cout<<"ERR, only one Player type are allowed "<<std::endl;
                    engien->quit();
                }
                else if(type.at(0) == '_')
                {
                    std::cout<<"No Additional (_) Type allowed in repeat";
                    engien->quit();
                }
                else
                {
                    std::cout<<std::endl<<"ERR : unreconigzed Type : "<< type << std::endl;
                    engien->quit();
                }
            }
        }
        else
        {
            std::cout<<std::endl<<"ERR : unreconigzed Type : "<< type << std::endl;
            engien->quit();
        }
    }

}

void SceneGame::sDoAction(const Action& action)
{
    if(action.type() == "START")
    {
        if(action.name() == "BoundingBox")
        {
            m_bounding_box_on = m_bounding_box_on == true ? false : true;
            return;
        }
        if(action.name() == "restart")
        {
            this->init();//loadLevel("Assets/Game/Levels/level_1.lvl");
            return;
        }
        if(action.name() == "Fps")
        {
            m_fps_on = m_fps_on == true ? false : true;
            return;
        }
        if(action.name() == "Tux")
        {
            m_tux_on = m_tux_on == true ? false : true;
        }
        if(action.name() == "Grid")
        {
            m_grid_on = m_grid_on == true ? false : true;
        }
        if(action.name() == "DLeft")
        {
            m_player->getComponent<CInput>().left = true;
            return;
        }
        if(action.name() == "DRight")
        {
            m_player->getComponent<CInput>().right = true;
            return;
        }
        if(action.name() == "DUp")
        {
            m_player->getComponent<CInput>().jump = true;
            return;
        }
        if(action.name() == "DDown")
        {
            m_player->getComponent<CInput>().down = true;
            return;
        }
        if(action.name() == "Shoot")
        {
            spawnBullet();
        }
    }
    else
    {
        if(action.name() == "DLeft")
        {
            m_player->getComponent<CInput>().left = false;
            return;
        }
        if(action.name() == "DRight")
        {
            m_player->getComponent<CInput>().right = false;
            return;
        }
        if(action.name() == "DUp")
        {
            m_player->getComponent<CInput>().jump = false;
            return;
        }
        if(action.name() == "DDown")
        {
            m_player->getComponent<CInput>().down = false;
            return;
        }
    }
}

void SceneGame::spawnPlayer()
{
    Vec2 player_pos(m_player_config.Gx, m_player_config.Gy);
    m_player = entites.addEntity("Player");
    m_player->addComponent<CTransform>(player_pos,Vec2(1),Vec2(0));
    auto& anim = engien->getAssets().getAnimation(m_player_config.anim);
    m_player->addComponent<CAnimation>(anim, true);
    m_player->getComponent<CTransform>().position = gridToPixel(player_pos, m_player);
    m_player->addComponent<CBoundingBox>(Vec2(m_player_config.Cw, m_player_config.Ch));
    m_player->addComponent<CGravity>(980.f);
    m_player->addComponent<CState>("idel");
    m_player->addComponent<CInput>();
}

void SceneGame::spawnBullet()
{
    auto e = entites.addEntity("bullet");
    const Vec2 bullet_vel = {m_player->getComponent<CTransform>().isRight == true ? +600 : -600, 0};
    e->addComponent<CTransform>(m_player->getComponent<CTransform>().position, Vec2(1), bullet_vel);
    e->addComponent<CLifespan>(1);
    e->addComponent<CAnimation>(engien->getAssets().getAnimation("bullet"), true);
    e->addComponent<CBoundingBox>(Vec2(2));
}

void SceneGame::spawnCoin(const std::shared_ptr<Entity>& e)
{
    auto en = entites.addEntity("coin");
    en->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().position.x,e->getComponent<CTransform>().position.y - e->getComponent<CBoundingBox>().size.y));
    en->addComponent<CAnimation>(engien->getAssets().getAnimation("coin"), false);
}

Vec2 SceneGame::gridToPixel(const Vec2& grid_pos, const std::shared_ptr<Entity>& e)
{
    Vec2 grid_cords_pixel = {grid_pos.x * m_grid.x, grid_pos.y * m_grid.y};
    auto win_inv = engien->getWindow().getSize().y;
    auto& scale = e->getComponent<CTransform>().scale;
    Vec2 size = {e->getComponent<CAnimation>().animation.size()/*.x * scale.x,
    entity->getComponent<CAnimation>().animation.size().y * scale.y*/};
    Vec2 pos = {grid_cords_pixel.x + size.x / 2, win_inv - (grid_cords_pixel.y + size.y/2)};
    //pos.x += size.x/2 * (scale.x);
    //pos.y += (scale.y) * size.y/2;
//    std::cout<<size.x<<" , "<<e->getComponent<CAnimation>().animation.size().y<<std::endl;
    return pos;
}

void SceneGame::sMovment(const std::shared_ptr<Entity>& e)
{
movePlayer();
    m_view.setCenter(m_player->getComponent<CTransform>().prev_position.x + 200, m_player->getComponent<CTransform>().prev_position.y - 100);
    //for(auto e : entites.getEntites())
    {
        if(e->hasComponent<CGravity>())
        {
            if(e->getComponent<CTransform>().velocity.y < m_player_config.Ms)
                e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity * m_delta;
            else
                e->getComponent<CTransform>().velocity.y = m_player_config.Ms;
        }
        if(e->hasComponent<CTransform>() && e->hasComponent<CAnimation>())
        {
            e->getComponent<CAnimation>().animation.getSprite().setScale(e->getComponent<CTransform>().scale.toSfVec());
            Vec2 scale = e->getComponent<CTransform>().scale;
            Vec2 tux_size = e->getComponent<CAnimation>().animation.size();//{e->getComponent<CAnimation>().animation.getSprite().getTexture()->getSize().x,
            //e->getComponent<CAnimation>().animation.getSprite().getTexture()->getSize().y};
            Vec2 t = {tux_size.x * scale.x, tux_size.y * scale.y};
            e->getComponent<CAnimation>().animation.getSprite().setOrigin((t/2).toSfVec());

            e->getComponent<CTransform>().prev_position = e->getComponent<CTransform>().position;
            e->getComponent<CTransform>().position += e->getComponent<CTransform>().velocity * m_delta;
                                //sCollision(e);
            e->getComponent<CAnimation>().animation.getSprite().setPosition((e->getComponent<CTransform>().position).toSfVec());
        }
    }

}

void SceneGame::sRender(const std::shared_ptr<Entity>& e)
{
    //for(auto e : entites.getEntites())
    {
        if(e->hasComponent<CAnimation>() && e->hasComponent<CTransform>())
        {
            if(m_tux_on)
            {
                if(Physics::pointInAABB(e->getComponent<CTransform>().position,m_view.getSize(),m_view.getCenter()))
                {
                    engien->getWindow().draw(e->getComponent<CAnimation>().animation.getSprite());
                    m_drawn++;
                }
            }
        }
        if(m_bounding_box_on)
            showBoundingBox(e);
        if(m_grid_on)
            drawGrid();
        if(m_fps_on)
            showFps();
    }
  //  engien->getWindow().display();
}

void SceneGame::drawGrid()
{
        if(m_same_frame) {return;}
        const auto& wins = engien->getWindow().getSize();
		unsigned int cols = ceil(wins.x/m_grid.x);
		unsigned int rows = ceil(wins.y/m_grid.y);
		unsigned int dots = 2*(rows + cols - 2);
		sf::VertexArray v(sf::Lines, dots);
		for(unsigned int i = 0; i < rows - 1;++i)
		{
			v[(i * 2)].position = sf::Vector2f(0, wins.y-(i+1)*m_grid.y);
			v[((i*2)+1)].position = sf::Vector2f(wins.x,wins.y - ((i+1)*m_grid.y));
		}
		for(unsigned int i = rows -1; i < dots / 2 ;++i)
		{
			v[i * 2].position = sf::Vector2f((i-rows+2)*m_grid.x,0);
			v[(i*2)+1].position = sf::Vector2f((i-rows+2)*m_grid.x,wins.y);
		}
        engien->getWindow().draw(v);
        m_same_frame = true;
}

void SceneGame::showFps()
{
    m_text.setString(std::to_string(engien->getFps()));
    m_text.setPosition(m_view.getCenter() - sf::Vector2f(m_view.getSize().x/2, m_view.getSize().y/2));
    engien->getWindow().draw(m_text);
}

void SceneGame::showBoundingBox(const std::shared_ptr<Entity>& e)
{
    if(e->hasComponent<CBoundingBox>())
        {
            auto& c_size = e->getComponent<CBoundingBox>().size;
            sf::RectangleShape r(c_size.toSfVec());
            r.setPosition((e->getComponent<CTransform>().position).toSfVec());
            r.setOrigin((c_size/2).toSfVec());
            r.setFillColor(sf::Color(0,0,0,0));
            r.setOutlineThickness(-2);
            r.setOutlineColor(sf::Color(0, 20, 230, 180));
            engien->getWindow().draw(r);
        }
}

void SceneGame::movePlayer()
{
    if(m_player->getComponent<CInput>().jump && m_player->getComponent<CInput>().can_jump)
    {
        m_player->getComponent<CTransform>().velocity.y = -m_player_config.Js;
    }
    if(m_player->getComponent<CInput>().left)
    {
        m_player->getComponent<CTransform>().velocity.x = Physics::movetowards(m_player->getComponent<CTransform>().velocity.x, -m_player_config.S, m_delta * 15);
    }
    else if(m_player->getComponent<CInput>().right)
    {
        m_player->getComponent<CTransform>().velocity.x = Physics::movetowards(m_player->getComponent<CTransform>().velocity.x, m_player_config.S, m_delta * 15);
    }
    else
    {
        m_player->getComponent<CTransform>().velocity.x = Physics::movetowards(m_player->getComponent<CTransform>().velocity.x, 0 , m_delta * 15);
    }
}

void SceneGame::sCollision(const std::shared_ptr<Entity>& e)
{
   const auto ol = Physics::getPrevOverLap(m_player, e);
   if(Physics::isOverLap(m_player, e))
   {
       if(e->tag() == "qblock" && e->getComponent<CState>().state != "dead")
        {
            if(m_player->getComponent<CTransform>().position.y > e->getComponent<CTransform>().position.y && ol.x > 0)
              {
                    e->getComponent<CState>().state = "dead";
                    spawnCoin(e);
              }
        }
        if(e->id() != m_player->id() && e->tag() != "bullet")
        {
            if(m_player->getComponent<CTransform>().position.y < e->getComponent<CTransform>().position.y && ol.x > 0)
                m_player->getComponent<CInput>().can_jump = true;
            Physics::normalResolution(m_player, e, m_delta);
        }
    }
    else
        m_player->getComponent<CInput>().can_jump = false;
    for(auto en : entites.getEntites())
    {
        if(Physics::pointInAABB(e->getComponent<CTransform>().position,m_view.getSize(),m_view.getCenter()))
        {
            if(en->id() == m_player->id() || e->id() == m_player->id()) continue;
            if(Physics::isOverLap(e, en))
            {
                if(e->tag() == "bullet")
                {
                    if(en->tag() == "TileB")
                        en->getComponent<CState>().state = "broken";
                    if(e->id() != en->id())
                        e->destroy();
                }
            }
        }
    }
}

void SceneGame::sLifespan(const std::shared_ptr<Entity>& e)
{
    if(e->hasComponent<CLifespan>())
    {
        e->getComponent<CLifespan>().remaining -= (e->getComponent<CLifespan>().life_span * m_delta)/e->getComponent<CLifespan>().life_span;
    if(e->getComponent<CLifespan>().remaining <= 0)
        e->destroy();
    }
}

void SceneGame::sAnimation(const std::shared_ptr<Entity>& e)
{
    if(e->getComponent<CAnimation>().animation.finished()) e->destroy();
    if(m_player->getComponent<CTransform>().velocity.x > 0)//position.x > m_player->getComponent<CTransform>().prev_position.x)
    {
        m_player->getComponent<CState>().state = "walk";
        m_player->getComponent<CTransform>().isRight = true;
    }
    else if(m_player->getComponent<CTransform>().velocity.x < 0)//position.x < m_player->getComponent<CTransform>().prev_position.x)
    {
        m_player->getComponent<CState>().state = "walk";
        m_player->getComponent<CTransform>().isRight = false;
    }
    else m_player->getComponent<CState>().state = "idel";
    if(m_player->getComponent<CTransform>().velocity.y < 0) m_player->getComponent<CState>().state = "jump";
    else if(m_player->getComponent<CTransform>().velocity.y > 69)m_player->getComponent<CState>().state = "fall";
    if(e->hasComponent<CState>())
    {
        if(e->getComponent<CState>().state == "dead")
        {
            e->getComponent<CAnimation>().animation = engien->getAssets().getAnimation("qblock_dead");
        }
        else if(e->getComponent<CState>().state == "broken")
        {
            const auto& en = entites.addEntity("anim");
            en->addComponent<CTransform>(e->getComponent<CTransform>().position);
            en->addComponent<CAnimation>(engien->getAssets().getAnimation("explosion1"), false);
            e->destroy();
        }
    }
    const std::string& state = m_player->getComponent<CState>().state;
    auto& anim = engien->getAssets().getAnimation("player_"+state);
    if(anim.name() != m_player->getComponent<CAnimation>().animation.name())
        m_player->getComponent<CAnimation>().animation = anim;
    m_player->getComponent<CAnimation>().animation.setRight(m_player->getComponent<CTransform>().isRight);
    e->getComponent<CAnimation>().animation.update(m_delta);
}

void SceneGame::update(float delta)
{
    m_delta = delta;
    entites.update();
    engien->getWindow().clear(sf::Color(0,70,240,169));
    for(auto e : entites.getEntites())
    {
        sMovment(e);
        sLifespan(e);
    if(Physics::pointInAABB(e->getComponent<CTransform>().position, m_view.getSize(), m_view.getCenter()))
        {
        sAnimation(e);
        sCollision(e);
    engien->getWindow().setView(m_view);
        sRender(e);
        }
    }
    std::cout<<m_drawn<<std::endl;
    m_drawn = 0;
    engien->getWindow().display();
}

