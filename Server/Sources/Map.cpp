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
    this->DeathHandler();

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
                    if(bullet->IsOverlapping(allplayers) &&
                       !allplayers->IsDead)
                    {
                        bullet->SetDeactive();
                        allplayers->ApplyDamage(bullet->Damage);

                        this->CheckDeath(allplayers, player);
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

void Map::CheckDeath(Player* victim, Player* Moderer)
{
    if(victim->IsDead)
    {
        // # Player Dead notification 
        NotificationList.push_back
        (
            BuildDeathInput(victim)
        );
        
        // # Kill notification 
        NotificationList.push_back
        (
            BuildKillNotification(victim, Moderer)
        );
    }
    else
    {
        NotificationList.push_back
        (
            BuildDamageInput(victim)
        );
    }
}

std::string Map::BuildDeathInput(Player* victim)
{
    std::string Packet = "2";
    Packet.push_back(victim->PID);

    return Packet;
}

std::string Map::BuildKillNotification(Player* victim, Player* Moderer)
{
    std::string Packet = "7";
    Packet.push_back(victim->PID);
    Packet.push_back(Moderer->PID);

    return Packet;
}

std::string Map::BuildDamageInput(Player* victim)
{
    std::string Packet = "8";
    Packet.push_back(victim->PID);
    Packet += *victim->GetStrHP();

    return Packet;
}

void Map::DeathHandler()
{
    for(auto player : PlayerList)
    {
        if(player->IsReborn)
        {
            std::string Packet = "4";
            Packet.push_back(player->PID);
            this->NotificationList.push_back(Packet);

            player->IsReborn = false;
            player->CallReborn();
        }
    }
}

