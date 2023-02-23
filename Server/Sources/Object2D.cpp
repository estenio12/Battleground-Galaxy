#include "../Includes/Object2D.hpp"

bool Object2D::IsOverlapping(class Object2D* Target)
{
    if(this->CollisionType != CollisionChannel::NO_COLLISION &&
       Target->CollisionType != CollisionChannel::NO_COLLISION)
    {
        return this->BoundingBox.intersects(Target->BoundingBox);
    }

    return false;
}

void Object2D::UpdateBoundingBox()
{
    this->BoundingBox.left   = this->Location.x;
    this->BoundingBox.top    = this->Location.y;
    this->BoundingBox.width  = this->Size.x;
    this->BoundingBox.height = this->Size.y;
}