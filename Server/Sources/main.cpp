#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

// const int SERVER_PORT = 46355;

#include "../Includes/ArgumentProcess.hpp"
#include "../Includes/DisplayInfo.hpp"
#include "../Includes/Map.hpp"
#include "../Includes/NetworkJob.hpp"

void Listening(NetworkJob* );

int main(int argc, char** argv)
{
    sf::RenderWindow Window(sf::VideoMode(600, 200), "Battleground Galaxy - Server", sf::Style::Close);
    sf::Event WindowEvent;

    // # App Setting
    Window.setFramerateLimit(60.f);

    // # Process Players
    std::string Argument = argv[1];
    auto GetPlayers = ArgumentProcess::Process(Argument);
    Map* map = new Map(GetPlayers);
    NetworkJob* Job = new NetworkJob(map);

    // # Start thread to listenning player input
    sf::Thread NetThread(&Listening, Job);
    NetThread.launch();
    
    // # Load Display
    auto Info = new DisplayInfo();

    while(Window.isOpen())
    {
        while(Window.pollEvent(WindowEvent))
        {
            if(WindowEvent.type == sf::Event::Closed)
            {
                Window.close();
                NetThread.terminate();
            }
        }

        map->Update();

        Window.clear();

        Info->Render(&Window);

        Window.display();
    }

    return EXIT_SUCCESS;
}

void Listening(NetworkJob* Job)
{
    while(Job->MatchRun())
    {
        Job->ReceiveData();
        Job->UpdateAllPlayers();
    }
}