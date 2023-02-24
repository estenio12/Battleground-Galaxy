// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <SFML/Graphics.hpp>

#include "../Helpers/Definitions.hpp"
#include "../Includes/Object2D.hpp"

class Bullet : public Object2D
{
    private:
        float movespeed = 1.f;
        sf::Vector2f Velocity;
        char Direction = INPUT::RIGHT;

    public:
        bool Active = false;

    public:
        Bullet();
        ~Bullet();

    public:
        void Update() override;

    public:
        void SetActive(sf::Vector2f, char Direction, char Type);
        void SetDeactive();

    private:
        void BulletMoviment();

    private:
        void LoadBullet(char Type);
        void LoadBasic();
        void LoadQuantumBubble();
        void LoadLaser();
};





