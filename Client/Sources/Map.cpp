#include "../Includes/Map.hpp"

Map::Map(RetArgPro* Argument,
         sf::Texture Texture):Texture(Texture)
{
    this->MyPlayer   = Argument->MyPlayer;
    this->PlayerList = Argument->PlayerList;
    this->ApplyColorToPlayers();
    
    LoadBlockCollision();

    this->ShotTimer = new Timer(0.5f);
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

        for(auto bullet : MyPlayer->BulletList)
        {
            if(bullet->IsOverlapping(block))
            {
                bullet->SetDeactive();
            }
        }
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

    // # Timers
    this->CanShotHandler();
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
    BlockCollision* b1 = new BlockCollision(sf::Vector2f(0, 550),
                                            sf::Vector2f(900, 250),
                                            true);
    BlockCollision* b2 = new BlockCollision(sf::Vector2f(0, 50),
                                            sf::Vector2f(50, 900),
                                            true);
    BlockCollision* b3 = new BlockCollision(sf::Vector2f(850, 50),
                                            sf::Vector2f(50, 900),
                                            true);
    BlockCollision* b4 = new BlockCollision(sf::Vector2f(0, 0),
                                            sf::Vector2f(1000, 50),
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

bool Map::MyPlayerIsLive()
{
    return this->MyPlayer->IsDead == false;
}

void Map::NetPacketProcess(std::string NetPacket)
{
    if(NetPacket.at(0) == NETCODE_CMD::KILLNOTIFIER)
    {
        // TO DO
    }

    // # Check if the input to MyPlayer
    if(NetPacket.at(1) == MyPlayer->PID)
    {
        auto Buffer = std::make_shared<std::string>(NetPacket);
        MyPlayer->NetInputProcess(Buffer);
    }
    else
    {
        // # Check if the input it to the outher players
        for(auto player : PlayerList)
        {
            if(player->PID == NetPacket.at(1))
            {
                auto Buffer = std::make_shared<std::string>(NetPacket);
                player->NetInputProcess(Buffer);
            }
        }
    }
}

void Map::Shot()
{
    this->CanShot = false;
    ShotTimer->ResetTimer();
}

void Map::CanShotHandler()
{
    if(!CanShot)
    {
        if(ShotTimer->ExecuteTimer())
        {
            this->CanShot = true;
        }
    }
}

void Map::UpdatePlayerInfo(std::string Packet)
{
    auto GetList = Tools::Split(Packet, ':');

    for(auto item : GetList)
    {
        this->NetPacketProcess(item);
    }
}

void Map::ApplyColorToPlayers()
{
    this->MyPlayer->SetHPColor(MyPlayerColor);

    for(auto player : PlayerList)
    {
        player->SetHPColor(EnemyPlayerColor);
    }
}
