#include "../Includes/Player.hpp"

void Player::NetInputProcess(std::shared_ptr<std::string> Input)
{
    switch(Input->at(0))
    {
        case NETCODE_CMD::REPLICATE:
            NetReplicante(Input);
        break;

        case NETCODE_CMD::UPDATEINFO:
            NetUpdateInfo(Input);
        break;

        case NETCODE_CMD::DEAD:
            NetDeath();
        break;

        case NETCODE_CMD::DISCONNECTED:
            NetDisconnect();
        break;

        case NETCODE_CMD::REBORN:
            NetReborn();
        break;

        case NETCODE_CMD::BONUS:
            NetActiveBonus(Input);
        break;

        case NETCODE_CMD::GUN:
            NetActiveGun(Input);
        break;
    }
}

void Player::NetReplicante(std::shared_ptr<std::string> Input)
{
    this->Move(Input->at(2));
    this->TriggerFire(Input->at(3));
}

void Player::NetUpdateInfo(std::shared_ptr<std::string> Input)
{
    this->HP = ConvertToFloat(*Substring(*Input, 2, 5));
    
    auto loc = GetLocation(*Input);
    this->Location.x = loc[0];
    this->Location.y = loc[1];
}

void Player::NetActiveBonus(std::shared_ptr<std::string> Input)
{
    this->Bonus = Input->at(2);
}

void Player::NetActiveGun(std::shared_ptr<std::string> Input)
{
    this->GUNHOLD = Input->at(2);
}

void Player::NetDisconnect()
{
    this->Disconnected = true;
}

void Player::NetDeath()
{
    this->IsDead = true;
}

void Player::NetReborn()
{
    this->CallReborn();
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

std::vector<float> Player::GetLocation(std::string Value)
{
    std::vector<float> locVec = {0.f, 0.f};
    std::string Split[2] = {"", ""};
    int indice = 0;

    std::string Temp = *Substring(Value, 6, Value.size());
    
    for(int i = 0; i < Temp.size(); i++)
    {
        if(Temp[i] == '|')
        {
            indice = 1;
        }
        else
        {
            Split[indice].push_back(Temp.at(i));
        }
    }

    locVec[0] = ConvertToFloat(Split[0]);
    locVec[1] = ConvertToFloat(Split[1]);

    return locVec;
}



