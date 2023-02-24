#include "../Includes/Player.hpp"

void Player::NetInputProcess(std::shared_ptr<std::string> Input)
{
    switch(Input->at(0))
    {
        case NETCODE_CMD::REPLICATE:
            NetReplicante(Input);
        break;

        case NETCODE_CMD::DISCONNECTED:
            NetDisconnect();
        break;
    }
}

void Player::NetReplicante(std::shared_ptr<std::string> Input)
{
    this->Move(Input->at(2));
    this->TriggerFire(Input->at(3));
}

void Player::NetDisconnect()
{
    this->Disconnected = true;
}

int Player::ConvertToInt(std::string Value)
{
    if(Value.empty())
    {
        return 0;
    }

    return std::stoi(Value);
}

float Player::ConvertToFloat(std::string Value)
{
    if(Value.empty())
    {
        return 0;
    }

    return std::stof(Value);
}

std::shared_ptr<std::string> Player::Substring(std::string Target, int start, int end)
{
    std::string Temp = "";

    for(int i = start; i < end; i++)
    {
        Temp.push_back(Target[i]);
    }

    return std::make_shared<std::string>(Temp);
}

