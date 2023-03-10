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
    public:
        sf::Vector2f Location;
        sf::Vector2f Size;
        uint8_t CollisionType = CollisionChannel::NO_COLLISION;
        sf::FloatRect BoundingBox;

    public:
        virtual void Update() = 0;
        
    public:
        bool IsOverlapping(class Object2D* Target);
        void UpdateBoundingBox();
};