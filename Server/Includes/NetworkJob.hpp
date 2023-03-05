// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <string>
#include <iostream>
#include <SFML/Network.hpp>

#include "../Helpers/Definitions.hpp"
#include "../Includes/Map.hpp"

class NetworkJob
{
    private:
        sf::UdpSocket Socket;
        unsigned short SERVERPORT = 46355;

    private:
        char Buffer[1024];
        size_t PacketSize;
        sf::IpAddress RemoteIP;
        unsigned short RemotePORT;

    private:
        Map* map;
        Timer* TimeUpdate;

    private:
        const float TIME_TO_UPDATE = 1.5f;

    public:
        NetworkJob(Map* );
        ~NetworkJob();

    public:
        void UpdateAllPlayers();

    private:
        void NotifyPlayers();

    public:
        void SendInputToAllPlayer(std::string );
        void SendInputSinglePlayer(std::string );
        void ReceiveData();
        bool MatchRun();
};