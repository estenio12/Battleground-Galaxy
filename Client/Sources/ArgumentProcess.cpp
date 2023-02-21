#include "../Includes/ArgumentProcess.hpp"

RetArgPro* ArgumentProcess::Process(std::string Value, sf::Texture SpriteSheet)
{
    RetArgPro* Temp = new RetArgPro();
    auto Entities = ArgumentProcess::Split(Value, '|');
    
    // # Others players
    for(int i = 1; i < Entities.size(); i++)
    {
        auto PlayerData = ArgumentProcess::Split(Entities[i], ':');
        Player* player = new Player(SpriteSheet);
        player->PID = PlayerData[0][0];
        player->Nickname = PlayerData[1];

        Temp->PlayerList.push_back(player);
    }

    // # MyPlayer
    auto PlayerData = ArgumentProcess::Split(Entities[0], ':');
    Player* player = new Player(SpriteSheet);
    player->PID = PlayerData[0][0];
    player->Nickname = PlayerData[1];

    Temp->MyPlayer = player;

    return Temp;
}

std::vector<std::string> ArgumentProcess::Split(std::string Value, char Target)
{
    std::vector<std::string> Temp;
    std::string TempItem = "";

    for(int i = 0; i < Value.size(); i++)
    {
        if(Value[i] == Target)
        {
            Temp.push_back(TempItem);
            TempItem.clear();
        }
        else
        {
            TempItem.push_back(Value[i]);
        }
    }

    if(!TempItem.empty())
    {
        Temp.push_back(TempItem);
        TempItem.clear();
    }

    return Temp;
}

