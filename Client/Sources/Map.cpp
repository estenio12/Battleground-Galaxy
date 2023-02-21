#include "../Includes/Map.hpp"

Map::Map(RetArgPro* Argument,
                           sf::Texture Texture):Texture(Texture)
{
    this->MyPlayer   = Argument->MyPlayer;
    this->PlayerList = Argument->PlayerList;
    
    LoadBlockCollision();
}

Map::~Map()
{
    delete MyPlayer;
    PlayerList.clear();
    CollisionList.clear();
}

void Map::Update()
{
    // # Update MyPlayer
    MyPlayer->Update();

    // # Update Bullet for MyPlayer
    for(auto bullet : MyPlayer->BulletList)
    {
        if(bullet->Active)
        {
            bullet->Update();
            
            for(auto allplayers : PlayerList)
            {
                if(bullet->IsOverlapping(allplayers))
                {
                    bullet->SetDeactive();
                }
            }
        }
    }

    // # Collision response for MyPlayer
    for(auto block : CollisionList)
    {
        MyPlayer->CollisionReponse(block);
    }

    // # Update All player
    for(auto player : PlayerList)
    {
        player->Update();

        // # Update block
        for(auto block : CollisionList)
        {
            // # Collision Response
            player->CollisionReponse(block);

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
                if(bullet->IsOverlapping(MyPlayer))
                {
                    bullet->SetDeactive();
                }

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

void Map::Render(sf::RenderWindow* Render)
{
    // # Render Block Collision for debug
    for(auto Block : CollisionList)
    {
        Block->Render(Render);
    }

    // # Render MyPlayer
    MyPlayer->Render(Render);

    // # Render All player
    for(auto player : PlayerList)
    {
        player->Render(Render);
    }
}

void Map::LoadBlockCollision()
{
    BlockCollision* b1 = new BlockCollision(sf::Vector2f(0, 450),
                                            sf::Vector2f(900, 250),
                                            true);
    BlockCollision* b2 = new BlockCollision(sf::Vector2f(0, 250),
                                            sf::Vector2f(50, 350),
                                            true);
    BlockCollision* b3 = new BlockCollision(sf::Vector2f(850, 250),
                                            sf::Vector2f(50, 350),
                                            true);
    BlockCollision* b4 = new BlockCollision(sf::Vector2f(100, 130),
                                            sf::Vector2f(350, 50),
                                            true);

    CollisionList.push_back(b1);
    CollisionList.push_back(b2);
    CollisionList.push_back(b3);
    CollisionList.push_back(b4);
}

char Map::GetMyPID()
{
    return this->MyPlayer->PID;
}

void Map::NetPacketProcess(std::string NetPacket)
{

}

