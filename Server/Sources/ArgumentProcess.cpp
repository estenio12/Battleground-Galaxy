#include "../Includes/ArgumentProcess.hpp"

RetArgPro* ArgumentProcess::Process(std::string Value)
{
    RetArgPro* Temp = new RetArgPro();
    auto Entities = ArgumentProcess::Split(Value, '|');
    
    for(int i = 0; i < Entities.size(); i++)
    {
        auto PlayerData = ArgumentProcess::Split(Entities[i], ':');
        char PID = PlayerData[0][0];
        std::string IP = PlayerData[1];
        int PORT = std::stoi(PlayerData[2]);

        Player* player = new Player(PID, IP, PORT);

        Temp->PlayerList.push_back(player);
    }

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

