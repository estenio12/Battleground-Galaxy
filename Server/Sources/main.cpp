#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

// const int SERVER_PORT = 46355;

int main(int argc, char** argv)
{
    sf::RenderWindow Window(sf::VideoMode(600, 200), "Battleground Galaxy - Server", sf::Style::Close);
    sf::Event WindowEvent;
    
    // # Server Text
    sf::Font font;
    sf::Text DisplayText;
    sf::Text DisplayIP;
    sf::Text DisplayPORT;
    sf::Text TextColorIP;
    sf::Text TextColorPORT;

    // # Variables
    const float FONT_SIZE = 25.f;

    // # App Setting
    Window.setFramerateLimit(60.f);
    font.loadFromFile("./Resource/Font/UbuntuRegular.ttf");
    DisplayText.setCharacterSize(FONT_SIZE);
    DisplayText.setFillColor(sf::Color::White);
    DisplayText.setFont(font);
    DisplayText.setPosition(sf::Vector2f(10.f, 10.f));
    DisplayIP.setCharacterSize(FONT_SIZE);
    DisplayIP.setFillColor(sf::Color::White);
    DisplayIP.setFont(font);
    DisplayIP.setPosition(sf::Vector2f(10.f, 35.f));
    DisplayPORT.setCharacterSize(FONT_SIZE);
    DisplayPORT.setFillColor(sf::Color::White);
    DisplayPORT.setFont(font);
    DisplayPORT.setPosition(sf::Vector2f(10.f, 60.f));
    TextColorIP.setCharacterSize(FONT_SIZE);
    TextColorIP.setFillColor(sf::Color::Yellow);
    TextColorIP.setFont(font);
    TextColorIP.setPosition(sf::Vector2f(45.f, 35.f));
    TextColorPORT.setCharacterSize(FONT_SIZE);
    TextColorPORT.setFillColor(sf::Color::Yellow);
    TextColorPORT.setFont(font);
    TextColorPORT.setPosition(sf::Vector2f(90.f, 60.f));

    sf::IpAddress GetIPServer = sf::IpAddress::getLocalAddress();
    
    // # Text
    DisplayText.setString("Server running in: ");
    DisplayIP.setString("IP: ");
    DisplayPORT.setString("PORT:");
    TextColorIP.setString(GetIPServer.toString());
    TextColorPORT.setString("46355");

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
        Window.draw(TextColorIP);
        Window.draw(TextColorPORT);

        Window.display();
    }

    return EXIT_SUCCESS;
}