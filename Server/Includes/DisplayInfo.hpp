// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class DisplayInfo
{
    public:
        sf::Font font;
        sf::Text DisplayText;
        sf::Text DisplayIP;
        sf::Text DisplayPORT;
        sf::Text TextColorIP;
        sf::Text TextColorPORT;

        const float FONT_SIZE = 25.f;

    public:
        DisplayInfo();
        ~DisplayInfo();

    public:
        void Render(sf::RenderWindow* );
};