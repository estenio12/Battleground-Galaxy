// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <SFML/Graphics.hpp>

#include "../Helpers/Definitions.hpp"
#include "../Includes/Object2D.hpp"

class BlockCollision: public Object2D
{
    private:
        sf::RectangleShape Debug;

    public:
        bool EnableDebug = false;

    public:
        BlockCollision(sf::Vector2f Location,
                       sf::Vector2f Size,
                       bool EnableDebug);
        ~BlockCollision();

        void Update() override;
        void Render(sf::RenderWindow* ) override;
};  

