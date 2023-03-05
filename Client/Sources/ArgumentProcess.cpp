#include "../Includes/ArgumentProcess.hpp"

RetArgPro* ArgumentProcess::Process(std::string Value, sf::Texture SpriteSheet)
{
    RetArgPro* Temp = new RetArgPro();
    auto Entities = Tools::Split(Value, '|');
    
    // # Others players
    for(int i = 1; i < Entities.size(); i++)
    {
        auto PlayerData = Tools::Split(Entities[i], ':');
        Player* player = new Player(SpriteSheet);
        player->PID = PlayerData[0][0];
        player->Nickname = PlayerData[1];

        Temp->PlayerList.push_back(player);
    }

    // # MyPlayer
    auto PlayerData = Tools::Split(Entities[0], ':');
    Player* player = new Player(SpriteSheet);
    player->PID = PlayerData[0][0];
    player->Nickname = PlayerData[1];

    Temp->MyPlayer = player;

    return Temp;
}

