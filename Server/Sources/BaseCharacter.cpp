#include "../Includes/BaseCharacter.hpp"

void BaseCharacter::Move(char Direction)
{
    this->BULLET_DIRECTION = Direction;
    
    if(!InJump)
    {
        this->InJump = true;
    }

    if(Direction == INPUT::LEFT)
    {
        Velocity.x = -(MOVESPEED * DELTATIME);
        Velocity.y = 0;
    }

    if(Direction == INPUT::RIGHT)
    {
        Velocity.x = MOVESPEED * DELTATIME;
        Velocity.y = 0;
    }

    if(Direction == INPUT::DOWN)
    {
        Velocity.y = MOVESPEED * DELTATIME;
        Velocity.x = 0;
    }

    this->Location += this->Velocity;

    this->UpdateBoundingBox();

    this->Velocity.x = 0;
    this->Velocity.y = 0;
}

void BaseCharacter::CollisionResponse(Object2D* Target)
{
    if(this->IsOverlapping(Target) && 
       Target->CollisionType == CollisionChannel::BLOCK)
    {
        // # Top Response
        if( this->Location.y < Target->Location.y 
            && this->Location.y + this->Size.y < Target->Location.y + Target->Size.y
            && this->Location.x < Target->Location.x + Target->Size.x
            && this->Location.x + this->Size.x > Target->Location.x )
        {
            this->Velocity.y = 0.f;
            this->Location.y = ( Target->Location.y - this->Size.y ) - 3;
            this->ResetJump();
        }

        // # Bottom Response
        else if( this->Location.y > Target->Location.y 
            && this->Location.y + this->Size.y > Target->Location.y + Target->Size.y 
            && this->Location.x < Target->Location.x + Target->Size.x
            && this->Location.x + this->Size.x > Target->Location.x ){

            this->Velocity.y = 0.f;
            this->Location.y = ( Target->Location.y + Target->Size.y ) + 3;
        }

        // # Left Response
        if( this->Location.x < Target->Location.x 
        && this->Location.x + this->Size.x < Target->Location.x + Target->Size.x
        && this->Location.y < Target->Location.y + Target->Size.y
        && this->Location.y + this->Size.y > Target->Location.y ){

            this->Velocity.x = 0.f;
            this->Location.x = ( Target->Location.x - this->Size.x ) - 3;
        }

        // # Right response
        else if( this->Location.x > Target->Location.x 
            && this->Location.x + this->Size.x > Target->Location.x + Target->Size.x 
            && this->Location.y < Target->Location.y + Target->Size.y 
            && this->Location.y + this->Size.y > Target->Location.y ){

            this->Velocity.x = 0.f;
            this->Location.x = ( Target->Location.x + Target->Size.x ) + 3;
        }

        this->UpdateBoundingBox();
    }
}

void BaseCharacter::ResetJump()
{
    this->InJump = false;
}

