#include "../Includes/Bullet.hpp"

Bullet::Bullet(sf::Texture Texture):Texture(Texture)
{
    this->CollisionType = CollisionChannel::OVERLAP;
    this->Sprite.setTexture(Texture);
    this->SetDeactive();
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

void Bullet::Render(sf::RenderWindow* Render)
{
    if(this->Active)
    {
        Render->draw(Sprite);
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
    this->Sprite.setTextureRect(sf::IntRect(0, 0,
                                            BULLET::BASIC_SIZE[0], 
                                            BULLET::BASIC_SIZE[1]));
    this->Size = sf::Vector2f(BULLET::BASIC_SIZE[0], 
                              BULLET::BASIC_SIZE[1]);
    this->movespeed = 10.f;
}

void Bullet::LoadLaser()
{
    this->Sprite.setTextureRect(sf::IntRect(0, 0, 
                                            BULLET::LASER_SIZE[0],
                                            BULLET::LASER_SIZE[1]));
    this->Size = sf::Vector2f(BULLET::LASER_SIZE[0], 
                              BULLET::LASER_SIZE[1]);
    this->movespeed = 25.f;
}

void Bullet::LoadQuantumBubble()
{
    this->Sprite.setTextureRect(sf::IntRect(0, 0, 
                                            BULLET::QUANTUMBUBBLE_SIZE[0],
                                            BULLET::QUANTUMBUBBLE_SIZE[1]));
    this->Size = sf::Vector2f(BULLET::QUANTUMBUBBLE_SIZE[0], 
                              BULLET::QUANTUMBUBBLE_SIZE[1]);
    this->movespeed = 10.f;
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
    this->Sprite.setPosition(Location);

}

void Bullet::SetDeactive()
{
    this->Active = false;
    this->Location = sf::Vector2f(10000.f, 10000.f);
    this->Sprite.setPosition(this->Location);
}
