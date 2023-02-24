#include "../Includes/Block.hpp"

BlockCollision::BlockCollision(sf::Vector2f Location,
                               sf::Vector2f Size)
{
    this->Location = Location;
    this->Size     = Size;
    this->CollisionType = CollisionChannel::BLOCK;
    this->UpdateBoundingBox();
}

BlockCollision::~BlockCollision(){}

void BlockCollision::Update(){}

