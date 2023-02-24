// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Includes/Object2D.hpp"

class BaseCharacter : public Object2D
{
    public:
        const float MOVESPEED = 300.f;
        const float DELTATIME = 0.016f;
        const float JUMPHEIGHT = 100.f;
        sf::Vector2f Velocity;
        bool InJump = false;
        char BULLET_DIRECTION = INPUT::RIGHT;

    public:
        void Move(char Direction);
        void CollisionResponse(Object2D* );
        void ResetJump();
};