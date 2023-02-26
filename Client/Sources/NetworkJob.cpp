#include "../Includes/NetworkJob.hpp"

NetworkJob::NetworkJob(Map* map, int temp_port):map(map)
{
    Socket.bind(temp_port);
    std::cout << "Port: " << temp_port << std::endl;
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
        // std::cout << "Debug: " << NewPacket << std::endl;
    }
}

bool NetworkJob::MatchRun()
{
    return map->MatchRun;
}
bool NetworkJob::CanShot()
{
    return map->CanShot;
}

void NetworkJob::MakeShot()
{
    map->Shot();
}

