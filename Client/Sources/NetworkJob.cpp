#include "../Includes/NetworkJob.hpp"

NetworkJob::NetworkJob(Map* map):map(map)
{
    Socket.bind(sf::Socket::AnyPort);
}

NetworkJob::~NetworkJob(){}

void NetworkJob::SendInput(char Move, char Fire)
{
    // # Command ID
    std::string InputString = "0";
    // # Player PID
    InputString.push_back(map->GetMyPID());
    // # Player Move Input
    InputString.push_back(Move);
    // # Player Fire Input
    InputString.push_back(Fire);

    // # Send packet to server
    Socket.send(InputString.c_str(), 
                InputString.size() + 1, 
                IP_SERVER, SERVER_PORT);
}

void NetworkJob::SendDisconnect()
{
    std::string InputString = "1";
    InputString.push_back(map->GetMyPID());
}

void NetworkJob::ReceiveData()
{
    // # Getting packet from server
    sf::Socket::Status status = Socket.receive(Buffer, 
                                               sizeof(Buffer), 
                                               PacketSize, 
                                               RemoteIP,
                                               RemotePORT);

    if(status == sf::Socket::Done)
    {
        std::string NewPacket = Buffer;
        map->NetPacketProcess(NewPacket);
    }
}

bool NetworkJob::MatchRun()
{
    return map->MatchRun;
}
