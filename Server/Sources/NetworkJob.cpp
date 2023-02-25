#include "../Includes/NetworkJob.hpp"

NetworkJob::NetworkJob(Map* map):map(map)
{
    Socket.bind(SERVERPORT);
}

NetworkJob::~NetworkJob(){}

void NetworkJob::SendInputToAllPlayer(std::string Input)
{
    for(auto item : map->NetList)
    {
        // # Send packet to all clients
        Socket.send(Input.c_str(), 
                    Input.size() + 1, 
                    item->IP, item->PORT);
    }
}

void NetworkJob::SendInputSinglePlayer(std::string Input)
{

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
        SendInputToAllPlayer(NewPacket);
        // std::cout << "Debgu: " << NewPacket << std::endl;
    }
}


bool NetworkJob::MatchRun()
{
    return map->MatchRun;
}

