#include "../Includes/DisplayInfo.hpp"

DisplayInfo::DisplayInfo()
{
    sf::IpAddress GetIPServer = sf::IpAddress::getLocalAddress();

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
    
    // # Text
    DisplayText.setString("Server running in: ");
    DisplayIP.setString("IP: ");
    DisplayPORT.setString("PORT:");
    TextColorIP.setString(GetIPServer.toString());
    TextColorPORT.setString("46355");
}

DisplayInfo::~DisplayInfo(){}

void DisplayInfo::Render(sf::RenderWindow* Render)
{
    Render->draw(DisplayText);
    Render->draw(DisplayIP);
    Render->draw(DisplayPORT);
    Render->draw(TextColorIP);
    Render->draw(TextColorPORT);
}
