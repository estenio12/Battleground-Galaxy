#include "../Includes/Object2D.hpp"

bool Object2D::IsOverlapping(class Object2D* Target)
{
    if(this->CollisionType != CollisionChannel::NO_COLLISION &&
    Target->CollisionType != CollisionChannel::NO_COLLISION)
    {
        return this->BoundingBox.getGlobalBounds()
                .intersects(Target->BoundingBox.getGlobalBounds());
    }

    return false;
}

void Object2D::UpdateBoundingBox()
{
    this->BoundingBox.setPosition(this->Location);
    this->BoundingBox.setSize(this->Size);
}