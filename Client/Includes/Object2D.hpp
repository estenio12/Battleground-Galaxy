// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Helpers/Definitions.hpp"

class Object2D
{
    private:
        sf::RectangleShape BoundingBox;

    public:
        sf::Vector2f Location;
        sf::Vector2f Size;
        sf::Sprite Sprite;
        uint8_t CollisionType = CollisionChannel::NO_COLLISION;

    public:
        virtual void Update() = 0;
        virtual void Render(sf::RenderWindow* ) = 0;
        
    public:
        bool IsOverlapping(class Object2D* Target);
        void UpdateBoundingBox();
};