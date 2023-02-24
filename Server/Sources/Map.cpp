#include "../Includes/Map.hpp"

Map::Map(RetArgPro* Argument)
{
    this->PlayerList = Argument->PlayerList;
    
    LoadBlockCollision();
}

Map::~Map()
{
    PlayerList.clear();
    CollisionList.clear();
}

void Map::Update()
{
    // # Update All player
    for(auto player : PlayerList)
    {
        player->Update();

        // # Update block
        for(auto block : CollisionList)
        {
            // # Collision Response
            player->CollisionResponse(block);

            for(auto bullet : player->BulletList)
            {
                if(bullet->Active)
                {
                    if(bullet->IsOverlapping(block))
                    {
                        bullet->SetDeactive();
                    }
                }
            }
        }

        for(auto bullet : player->BulletList)
        {
            if(bullet->Active)
            {
                for(auto allplayers : PlayerList)
                {
                    if(bullet->IsOverlapping(allplayers))
                    {
                        bullet->SetDeactive();
                    }
                }
            }
        }
    }
}

void Map::LoadBlockCollision()
{
    BlockCollision* b1 = new BlockCollision(sf::Vector2f(0, 450),
                                            sf::Vector2f(900, 250));
    BlockCollision* b2 = new BlockCollision(sf::Vector2f(0, 250),
                                            sf::Vector2f(50, 350));
    BlockCollision* b3 = new BlockCollision(sf::Vector2f(850, 250),
                                            sf::Vector2f(50, 350));
    BlockCollision* b4 = new BlockCollision(sf::Vector2f(100, 130),
                                            sf::Vector2f(350, 50));

    CollisionList.push_back(b1);
    CollisionList.push_back(b2);
    CollisionList.push_back(b3);
    CollisionList.push_back(b4);
}

void Map::NetPacketProcess(std::string NetPacket)
{
    for(auto player : PlayerList)
    {
        if(player->PID == NetPacket.at(1))
        {
            auto Buffer = std::make_shared<std::string>(NetPacket);
            player->NetInputProcess(Buffer);
        }
    }
}

