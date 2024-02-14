#include "SceneGame.hpp"

#include "Phisics.hpp"

SceneGame::SceneGame(Engien* engien)
{
    this->engien = engien;
    init();
}

void SceneGame::init()
{
    loadLevel("Assets/Game/Levels/level_1.lvl");
    regesterAction(sf::Keyboard::Right, "DRight");
    regesterAction(sf::Keyboard::Left, "DLeft");
    regesterAction(sf::Keyboard::Up, "DUp");
    regesterAction(sf::Keyboard::Down, "DDown");
    regesterAction(sf::Keyboard::B, "BoundingBox");
    m_view = sf::View(sf::FloatRect(0 ,0 ,
    engien->getWindow().getSize().x, engien->getWindow().getSize().y));
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
        else if(type == "Tile")
        {
            float Cw,Ch;
            file_buffer >> name >> Gx >> Gy >> Cw >> Ch;
            auto e = entites.addEntity(name == "qblock" ? "qblock" : "Tile");
            if(name == "qblock")
                e->addComponent<CState>("untouched");
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
        else if(type.at(0) == '_')
        {
            type = type.substr(1, type.size());
        }
        else if(type == "repeat")
        {
            std::string dummy;
            int start, finsh;
            float Cw,Ch;
            file_buffer >> dummy >> start >> finsh;
            file_buffer >> type;
            for(int i = start; i < finsh; i++)
            {
                if(type == "Dec")
                {
                    if(i == start)
                        file_buffer >> name >> Gx >> dummy >> Gy >> dummy;
                    auto e = entites.addEntity(type);
                    auto& anim = engien->getAssets().getAnimation(name);
                    e->addComponent<CAnimation>(anim, true);
                    e->addComponent<CTransform>(gridToPixel(Vec2(Gx * i, Gy * i),e));
                }
                else if(type == "Tile")
                {
                    if(i == start)
                    {
                        file_buffer >> name >> Gx >> dummy >> Gy >> dummy >> Cw >> Ch;
                    }
                    auto e = entites.addEntity(type);
                    e->addComponent<CTransform>(Vec2(0), Vec2(1),Vec2(0));
                    auto& anim = engien->getAssets().getAnimation(name);
                    e->addComponent<CAnimation>(anim, true);
                    e->addComponent<CBoundingBox>(Vec2(Cw, Ch));
                    e->getComponent<CTransform>().position = gridToPixel(Vec2(Gx * i, Gy),e);
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
        }
        if(action.name() == "DLeft")
        {
            m_player->getComponent<CInput>().left = true;
            return;
        }

        if(action.name() == "DRight")
        {
            m_player->getComponent<CInput>().right = true;
            m_view.move(m_player_config.S*m_delta,0);
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
    m_player->addComponent<CGravity>(30.f);
    m_player->addComponent<CState>("idel");
    m_player->addComponent<CInput>();
}

Vec2 SceneGame::gridToPixel(const Vec2& grid_pos, std::shared_ptr<Entity> entity)
{
    Vec2 grid_cords_pixel = {grid_pos.x * m_grid.x, grid_pos.y * m_grid.y};
    auto win_inv = engien->getWindow().getSize().y;
    auto& scale = entity->getComponent<CTransform>().scale;
    Vec2 size = {entity->getComponent<CAnimation>().animation.size()/*.x * scale.x,
    entity->getComponent<CAnimation>().animation.size().y * scale.y*/};
    Vec2 pos = {grid_cords_pixel.x + size.x / 2, win_inv - (grid_cords_pixel.y + size.y/2)};
    //pos.x += size.x/2 * (scale.x);
    //pos.y += (scale.y) * size.y/2;
//    std::cout<<size.x<<" , "<<e->getComponent<CAnimation>().animation.size().y<<std::endl;
//    engien->quit();
    return pos;
}

void SceneGame::sMovment(std::shared_ptr<Entity> e)
{
    //m_view.setCenter(m_player->getComponent<CTransform>().position.toSfVec());
    movePlayer();
    //for(auto e : entites.getEntites())
    {
        if(e->hasComponent<CGravity>())
        {
            if(e->getComponent<CTransform>().velocity.y < m_player_config.Ms)
                e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;
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
            e->getComponent<CAnimation>().animation.getSprite().setPosition((e->getComponent<CTransform>().position).toSfVec());
        }
    }
}

void SceneGame::sRender()
{
    engien->getWindow().clear(sf::Color(255,0,0));
    drawGrid();
    for(auto e : entites.getEntites())
    {
        if(e->hasComponent<CAnimation>() && e->hasComponent<CTransform>())
        {
            if(m_tux_on)
                engien->getWindow().draw(e->getComponent<CAnimation>().animation.getSprite());
        }
        if(m_bounding_box_on)
            showBoundingBox(e);
    }
    engien->getWindow().display();
}


void SceneGame::drawGrid()
{
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



/*
    const auto& wins = engien->getWindow().getSize();
    unsigned int cols = ceil(wins.x/m_grid.x);
    unsigned int rows = ceil(wins.y/m_grid.y);
    unsigned int dots = 2 * (rows + cols +1);
    sf::VertexArray v(sf::Lines, dots);
    for(int i = 0; i < rows - 1;++i)
    {
        v[(i * 2)].position = sf::Vector2f(0, wins.y - (i+1) * m_grid.y);
        v[((i*2)+1)].position = sf::Vector2f(wins.x, wins.y - ((i+1)*m_grid.y));
    }
    for(int i = rows - 1; i < dots;i++)
    {
        v[i * 2].position = sf::Vector2f((i-rows+2)*m_grid.x,0);
        v[(i*2)+1].position = sf::Vector2f((i-rows+2)*m_grid.x,wins.y);
    }*/
    engien->getWindow().draw(v);

/*
for(int i = 0; i < 10; i++)
{
    for(int j = 0; j < 10; j++)
    {
        srand(time(0));
        sf::RectangleShape r(sf::Vector2f(64, 64));
        r.setOrigin(sf::Vector2f(0, 64));
        r.setPosition(i*64,engien->getWindow().getSize().y - j*64);
        r.setFillColor(sf::Color(rand()*333*i+3%255,j*66*rand()*35+9%255,rand()+i+j%255));
        engien->getWindow().draw(r);
    }
}
*/
}

void SceneGame::showBoundingBox(const std::shared_ptr<Entity> e)
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
    if(m_player->getComponent<CInput>().left) {m_player->getComponent<CTransform>().velocity.x = -1 * m_player_config.S;}
    else if(m_player->getComponent<CInput>().right)
    {
    {m_player->getComponent<CTransform>().velocity.x = m_player_config.S;}
    }
    else{m_player->getComponent<CTransform>().velocity.x = 0;}
    if(m_player->getComponent<CInput>().jump) {m_player->getComponent<CTransform>().velocity.y = -1 * m_player_config.Js;}
    //else {m_player->getComponent<CTransform>().velocity.y = 0;}
}

void SceneGame::sCollision()
{
    for(auto e : entites.getEntites())
    {
        if(e->tag() == "qblock")
        {
            if(Phisics::isOverLap(e, m_player))
            {
                if((e->getComponent<CTransform>().position.y + e->getComponent<CBoundingBox>().half_size.y
                    < m_player->getComponent<CTransform>().position.y + m_player->getComponent<CBoundingBox>().half_size.y))
                {
                    e->getComponent<CState>().state = "dead";
                    //e->getComponent<CTransform>().velocity.y = -10;
                }
            }
        }
        if(e->id() != m_player->id())
            Phisics::normalResolution(m_player, e);
    }
}


void SceneGame::sAnimation()
{
    for(auto e : entites.getEntites())
    {
        if(e->hasComponent<CTransform>() && e->hasComponent<CAnimation>())
        {
            e->getComponent<CAnimation>().animation.update(m_delta);
            auto v = e->getComponent<CTransform>().velocity.x;
            if(v < 0)
                e->getComponent<CAnimation>().animation.setRight(false);
            else if(v > 0)
                e->getComponent<CAnimation>().animation.setRight(true);
        }
        if(e->hasComponent<CState>())
        {
            if(e->getComponent<CState>().state == "dead")
            {
                e->getComponent<CAnimation>().animation = engien->getAssets().getAnimation("qblock_dead");
            }
        }
    }
    const std::string& state = m_player->getComponent<CState>().state;
    auto& anim = engien->getAssets().getAnimation("player_"+state);
    if(anim.name() != m_player->getComponent<CAnimation>().animation.name())
        m_player->getComponent<CAnimation>().animation = anim;
}

void SceneGame::update(float delta)
{
    m_delta = delta;
    entites.update();
    for(auto e : entites.getEntites())
    {
        sMovment(e);}
    engien->getWindow().setView(m_view);
            sCollision();

        sAnimation();

        sRender();
    //}
}

