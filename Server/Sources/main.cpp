#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

// const int SERVER_PORT = 46355;

int main(int argc, char** argv)
{
    sf::RenderWindow Window(sf::VideoMode(600, 500), "Battleground Galaxy - Server", sf::Style::Close);
    sf::Event WindowEvent;
    
    // # Server Text
    sf::Font font;
    sf::Text DisplayText;
    sf::Text DisplayIP;
    sf::Text DisplayPORT;

    // # App Setting
    Window.setFramerateLimit(60.f);
    font.loadFromFile("./Resource/Font/UbuntuRegular.ttf");
    DisplayText.setCharacterSize(16.f);
    DisplayText.setFillColor(sf::Color::White);
    DisplayText.setFont(font);
    DisplayText.setPosition(sf::Vector2f(10.f, 10.f));
    DisplayIP.setCharacterSize(16.f);
    DisplayIP.setFillColor(sf::Color::White);
    DisplayIP.setFont(font);
    DisplayIP.setPosition(sf::Vector2f(10.f, 30.f));
    DisplayPORT.setCharacterSize(16.f);
    DisplayPORT.setFillColor(sf::Color::White);
    DisplayPORT.setFont(font);
    DisplayPORT.setPosition(sf::Vector2f(10.f, 50.f));

    sf::IpAddress GetIPServer = sf::IpAddress::getLocalAddress();
    
    // # Text
    DisplayText.setString("Server running in: ");
    DisplayIP.setString("IP: " + GetIPServer.toString());
    DisplayPORT.setString("PORT: 46355");

    while(Window.isOpen())
    {
        while(Window.pollEvent(WindowEvent))
        {
            if(WindowEvent.type == sf::Event::Closed)
            {
                Window.close();
            }
        }

        Window.clear();

        Window.draw(DisplayText);
        Window.draw(DisplayIP);
        Window.draw(DisplayPORT);

        Window.display();
    }

    return EXIT_SUCCESS;
}