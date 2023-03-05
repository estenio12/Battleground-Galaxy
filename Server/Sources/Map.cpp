#include "../Includes/Map.hpp"

Map::Map(RetArgPro* Argument)
{
    this->PlayerList = Argument->PlayerList;
    
    LoadBlockCollision();
    LoadNetList();
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
    BlockCollision* b1 = new BlockCollision(sf::Vector2f(0, 550),
                                            sf::Vector2f(900, 250));

    BlockCollision* b2 = new BlockCollision(sf::Vector2f(0, 50),
                                            sf::Vector2f(50, 900));

    BlockCollision* b3 = new BlockCollision(sf::Vector2f(850, 50),
                                            sf::Vector2f(50, 900));
                                            
    BlockCollision* b4 = new BlockCollision(sf::Vector2f(0, 0),
                                            sf::Vector2f(1000, 50));

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

void Map::LoadNetList()
{
    for(auto item : PlayerList)
    {
        NetList.push_back(new NETPACKET::Packet(item->IP, item->PORT));
    }
}

std::shared_ptr<std::string> Map::GetPlayersData()
{
    std::string Packet;

    for(auto player : PlayerList)
    {
        Packet.push_back('1');
        Packet.push_back(player->PID);
        Packet += *player->GetStrHP();
        Packet += *player->GetStrLocation();
        Packet.push_back(':');
    }

    return std::make_shared<std::string>(Packet);
}


