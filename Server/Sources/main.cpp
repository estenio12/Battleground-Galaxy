#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

// const int SERVER_PORT = 46355;

#include "../Includes/ArgumentProcess.hpp"
#include "../Includes/DisplayInfo.hpp"
#include "../Includes/Map.hpp"

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
    
    // # Load Display
    auto Info = new DisplayInfo();

    while(Window.isOpen())
    {
        while(Window.pollEvent(WindowEvent))
        {
            if(WindowEvent.type == sf::Event::Closed)
            {
                Window.close();
            }
        }

        map->Update();

        Window.clear();

        Info->Render(&Window);

        Window.display();
    }

    return EXIT_SUCCESS;
}