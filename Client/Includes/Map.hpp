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
#include "../Includes/Timer.hpp"

class Map
{
    private:
        sf::Texture Texture;
        std::vector<Player*> PlayerList;
        Player* MyPlayer;
        Timer* ShotTimer;

    private:
        std::vector<BlockCollision*> CollisionList;

    private:

    public:
        bool MatchRun = true;
        bool CanShot  = true;

    public:
        Map(RetArgPro*, sf::Texture);
        ~Map();

    public:
        void Update();
        void Render(sf::RenderWindow* );
        void NetPacketProcess(std::string );
        char GetMyPID();
        void Shot();

    private:
        void LoadBlockCollision();
        void CanShotHandler();
};

