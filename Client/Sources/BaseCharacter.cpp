#include "../Includes/BaseCharacter.hpp"

void BaseCharacter::Move(char Direction)
{
    if(Direction == INPUT::UPLEFT)
    {
        Velocity.x = -((MOVESPEED * DELTATIME) / DIAGONAL_FACTOR);
        Velocity.y = -((MOVESPEED * DELTATIME) / DIAGONAL_FACTOR);
        this->BULLET_DIRECTION = INPUT::UPLEFT;
    }

    if(Direction == INPUT::UPRIGHT)
    {
        Velocity.x = (MOVESPEED * DELTATIME / DIAGONAL_FACTOR);
        Velocity.y = -((MOVESPEED * DELTATIME) / DIAGONAL_FACTOR);
        this->BULLET_DIRECTION = INPUT::UPRIGHT;
    }

    if(Direction == INPUT::DOWNLEFT)
    {
        Velocity.x = -((MOVESPEED * DELTATIME) / DIAGONAL_FACTOR);
        Velocity.y = (MOVESPEED * DELTATIME / DIAGONAL_FACTOR);
        this->BULLET_DIRECTION = INPUT::DOWNLEFT;
    }

    if(Direction == INPUT::DOWNRIGHT)
    {
        Velocity.x = (MOVESPEED * DELTATIME / DIAGONAL_FACTOR);
        Velocity.y = (MOVESPEED * DELTATIME / DIAGONAL_FACTOR);
        this->BULLET_DIRECTION = INPUT::DOWNRIGHT;
    }

    if(Direction == INPUT::UP)
    {
        Velocity.x = 0;
        Velocity.y = -(MOVESPEED * DELTATIME);
        this->BULLET_DIRECTION = INPUT::UP;
    }

    if(Direction == INPUT::LEFT)
    {
        Velocity.x = -(MOVESPEED * DELTATIME);
        Velocity.y = 0;
        this->BULLET_DIRECTION = INPUT::LEFT;
    }

    if(Direction == INPUT::RIGHT)
    {
        Velocity.x = MOVESPEED * DELTATIME;
        Velocity.y = 0;
        this->BULLET_DIRECTION = INPUT::RIGHT;
    }

    if(Direction == INPUT::DOWN)
    {
        Velocity.y = MOVESPEED * DELTATIME;
        Velocity.x = 0;
        this->BULLET_DIRECTION = INPUT::DOWN;
    }
}

void BaseCharacter::CollisionReponse(Object2D* Target)
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

        this->Sprite.setPosition(this->Location);
    }
}
