#include "../Includes/Block.hpp"

BlockCollision::BlockCollision(sf::Vector2f Location,
                               sf::Vector2f Size,
                               bool EnableDebug)
{
    this->Location = Location;
    this->Size     = Size;
    this->CollisionType = CollisionChannel::BLOCK;
    this->UpdateBoundingBox();

    // # For debug mode
    this->Debug.setFillColor(sf::Color::Red);
    this->Debug.setPosition(Location);
    this->Debug.setSize(Size);
    this->EnableDebug = EnableDebug;
}

BlockCollision::~BlockCollision(){}

void BlockCollision::Update(){}

void BlockCollision::Render(sf::RenderWindow* Render)
{
    if(this->EnableDebug)
    {
        Render->draw(this->Debug);
    }
}