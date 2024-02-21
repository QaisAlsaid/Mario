#pragma once
#include <fstream>
#include <iostream>
#include <string>

void laodLevelData(const std::string& path, EntityManager& entites, Engien* engien, PlayerConfig& player_config)
{
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
            e->addComponent<CTransform>(Vec2(Gx, Gy));
            auto& anim = engien->getAssets().getAnimation(name);
            e->addComponent<CAnimation>(anim, true);
        }
        else if(type == "Tile")
        {
            float Cw,Ch;
            file_buffer >> name >> Gx >> Gy >> Cw >> Ch;
            auto e = entites.addEntity("Tile");
            e->addComponent<CTransform>(Vec2(Gx, Gy));
            auto& anim = engien->getAssets().getAnimation(name);
            e->addComponent<CAnimation>(anim, true);
            e->addComponent<CBoundingBox>(Vec2(Cw, Ch));
        }
        else if(type == "Player")
        {
            file_buffer >> player_config.Gx >> player_config.Gy >> player_config.Cw >> player_config.Ch;
            file_buffer >> player_config.S >> player_config.Ms >> player_config.Js >> player_config.anim;
        }
        else if(type.at(0) == '_')
        {
            type = type.substr(1, type.size());
        }
        else if(type == "repeat")
        {
            std::string dummy;
            int start, finsh;
            file_buffer >> dummy >> start >> finsh;
            for(int i = start; i < finsh; i++)
            {
                file_buffer >> type;

                if(type == "Dec")
                {
                    file_buffer >> name >> Gx >> dummy >> Gy >> dummy;
                    auto e = entites.addEntity("Dec");
                    e->addComponent<CTransform>(gridToPixel(Vec2(Gx * i, Gy * i),e));
                    auto& anim = engien->getAssets().getAnimation(name);
                    e->addComponent<CAnimation>(anim, true);
                }
                else if(type == "Tile")
                {
                    float Cw,Ch;
                    file_buffer >> name >> Gx >> dummy >> Gy >> dummy >> Cw >> Ch;
                    auto e = entites.addEntity("Tile");
                    e->addComponent<CTransform>(Vec2(0), Vec2(4),Vec2(0));
                    e->getComponent<CTransform>().position = gridToPixel(Vec2(Gx * i, Gy * i),e);
                    auto& anim = engien->getAssets().getAnimation(name);
                    e->addComponent<CAnimation>(anim, true);
                    e->addComponent<CBoundingBox>(Vec2(Cw, Ch));
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
