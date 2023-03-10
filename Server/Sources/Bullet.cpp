#include "../Includes/Bullet.hpp"

Bullet::Bullet()
{
    this->CollisionType = CollisionChannel::OVERLAP;
}

Bullet::~Bullet(){}

void Bullet::Update()
{
    if(this->Active)
    {
        this->BulletMoviment();
        this->UpdateBoundingBox();
    }
}

void Bullet::SetActive(sf::Vector2f NewLocation, 
                       char Direction, 
                       char Type)
{
    this->Direction = Direction;
    this->LoadBullet(Type);
    this->Location = NewLocation;
    this->Active = true;
}

void Bullet::LoadBullet(char Type)
{
    switch(Type)
    {
        case GUN::BASIC:
            LoadBasic();
        break;

        case GUN::LASER:
            LoadLaser();
        break;

        case GUN::QUANTUNBUBBLE:
            LoadQuantumBubble();
        break;
    }
}

void Bullet::LoadBasic()
{
    this->Size = sf::Vector2f(BULLET::BASIC_SIZE[0], 
                              BULLET::BASIC_SIZE[1]);
    this->movespeed = 10.f;
    this->Damage = SYSATTR::DAMAGE::BASIC;
}

void Bullet::LoadLaser()
{
    this->Size = sf::Vector2f(BULLET::LASER_SIZE[0], 
                              BULLET::LASER_SIZE[1]);
    this->movespeed = 25.f;
    this->Damage = SYSATTR::DAMAGE::LASER;
}

void Bullet::LoadQuantumBubble()
{
    this->Size = sf::Vector2f(BULLET::QUANTUMBUBBLE_SIZE[0], 
                              BULLET::QUANTUMBUBBLE_SIZE[1]);
    this->movespeed = 10.f;
    this->Damage = SYSATTR::DAMAGE::QUANTUM_BUBBLE;
}

void Bullet::BulletMoviment()
{
    Velocity.x = 0.f;
    Velocity.y = 0.f;

    switch (Direction)
    {
        case INPUT::RIGHT:
            Velocity.x = movespeed;
            Velocity.y = 0.f;
        break;

        case INPUT::LEFT:
            Velocity.x = -movespeed;
            Velocity.y = 0.f;
        break;

        case INPUT::DOWN:
            Velocity.x = 0.f;
            Velocity.y = movespeed;
        break;

        case INPUT::UP:
            Velocity.x = 0.f;
            Velocity.y = -movespeed;
        break;

        case INPUT::UPLEFT:
            Velocity.x = -movespeed;
            Velocity.y = -movespeed;
        break;

        case INPUT::UPRIGHT:
            Velocity.x = movespeed;
            Velocity.y = -movespeed;
        break;

        case INPUT::DOWNLEFT:
            Velocity.x = -movespeed;
            Velocity.y = movespeed;
        break;

        case INPUT::DOWNRIGHT:
            Velocity.x = movespeed;
            Velocity.y = movespeed;
        break;
    }

    this->Location += Velocity;
}

void Bullet::SetDeactive()
{
    this->Active = false;
    this->Location = sf::Vector2f(10000.f, 10000.f);
}
