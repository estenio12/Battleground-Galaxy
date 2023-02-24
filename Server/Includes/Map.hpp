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
    private:
        std::vector<Player*> PlayerList;

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

    private:
        void LoadBlockCollision();
};

