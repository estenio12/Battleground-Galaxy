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

    private:
        void LoadBlockCollision();
};

