#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../Helpers/Definitions.hpp"
#include "../Includes/Map.hpp"
#include "../Includes/ArgumentProcess.hpp"
#include "../Includes/NetworkJob.hpp"

void Thread_Network(NetworkJob* Job);
void InputHandler(NetworkJob* Job);

int main(int argc, char** argv)
{
    // # Load Window & Global Assets
    sf::RenderWindow Window(sf::VideoMode(900, 600), "Battleground Galaxy", sf::Style::Default);
    sf::Event WindowEvent;
    sf::Texture SpriteSheet;
    sf::Font Font;

    // # Setting
    Window.setFramerateLimit(60.f);
    SpriteSheet.loadFromFile("./Resource/Assets/SpriteSheet.png");
    Font.loadFromFile("./Resource/Font/UbuntuRegular.ttf");

    // # Load Actors
    std::string Argument = argv[1];
    RetArgPro* GetPlayerList = ArgumentProcess::Process(Argument, SpriteSheet);

    int TMP_PORT = std::stoi(argv[2]);
    Map* map = new Map(GetPlayerList, SpriteSheet);
    NetworkJob* Job = new NetworkJob(map, TMP_PORT);

    // # Instanteate network thread
    sf::Thread NetThread(&Thread_Network, Job);
    NetThread.launch();

    // # Game Loop
    while (Window.isOpen())
    {
        while(Window.pollEvent(WindowEvent))
        {
            switch(WindowEvent.type)
            {
                case sf::Event::Closed:
                    Window.close();
                    NetThread.terminate();
                break;

                default: break;
            }
        }

        if(Window.hasFocus())
        {
            InputHandler(Job);
        }

        map->Update();

        Window.clear();

        map->Render(&Window);

        Window.display();
    }

    delete GetPlayerList;
    delete map;
    delete Job;

    return EXIT_SUCCESS;
}

void Thread_Network(NetworkJob* Job)
{
    while(Job->MatchRun())
    {
        // # Listining Server in background
        Job->ReceiveData();

        // # Stop thread for 1 milliseconds per cycle
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void InputHandler(NetworkJob* Job)
{
    char Fire = FIRE::NONE;
    char Move = INPUT::NONE;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Move = INPUT::LEFT;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        Move = INPUT::RIGHT;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            Move = INPUT::UPLEFT;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            Move = INPUT::UPRIGHT;
        }
        else
        {
            Move = INPUT::UP;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            Move = INPUT::DOWNLEFT;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            Move = INPUT::DOWNRIGHT;
        }
        else
        {
            Move = INPUT::DOWN;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && Job->CanShot())
    {
        Fire = FIRE::FIRE;
        Job->MakeShot();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        Fire = FIRE::BONUS;
    }
    
    Job->SendInput(Move, Fire);
}

