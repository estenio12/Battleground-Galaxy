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
        const int SERVER_PORT = 46355;
        const std::string IP_SERVER = "192.168.100.6";
        sf::UdpSocket Socket;

    private:
        char Buffer[1024];
        size_t PacketSize;
        sf::IpAddress RemoteIP;
        unsigned short RemotePORT;

    private:
        Map* map;

    public:
        NetworkJob(Map* );
        ~NetworkJob();

    public:
        void SendInput(char Input, char Fire);
        void SendDisconnect();
        void ReceiveData();
        bool MatchRun();
};