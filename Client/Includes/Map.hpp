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
#include "../Helpers/Tools.hpp"

class Map
{
    private:
        sf::Texture Texture;
        sf::Color MyPlayerColor    = sf::Color(104, 219, 54);
        sf::Color EnemyPlayerColor = sf::Color(232, 86, 76);;
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
        void UpdatePlayerInfo(std::string );
        bool MyPlayerIsLive();

    private:
        void LoadBlockCollision();
        void CanShotHandler();
        void ApplyColorToPlayers();
};

