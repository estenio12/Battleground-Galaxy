// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "../Includes/Player.hpp"
#include "../Includes/Block.hpp"
#include "../Includes/ArgumentProcess.hpp"

class Map
{
    public:
        std::vector<Player*> PlayerList;
        std::vector<NETPACKET::Packet*> NetList;
        std::vector<std::string> NotificationList;

    private:
        std::vector<BlockCollision*> CollisionList;

    private:

    public:
        bool MatchRun = true;

    public:
        Map(RetArgPro*);
        ~Map();

    public:
        void Update();
        void NetPacketProcess(std::string );
        void LoadNetList();
        std::shared_ptr<std::string> GetPlayersData();  

    private:
        void LoadBlockCollision();
        void CheckDeath(Player*, Player* );
        std::string BuildDeathInput(Player* );
        std::string BuildKillNotification(Player*, Player* );
        std::string BuildDamageInput(Player* );
        void DeathHandler();
};

