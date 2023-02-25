#include "../Includes/BaseCharacter.hpp"

void BaseCharacter::Move(char Direction)
{
    Velocity.x = 0;
    Velocity.y = 0;

    if(!InJump)
    {
        this->InJump = true;
        this->OnGround = false;
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

    this->Location += this->Velocity;

    this->Sprite.setPosition(this->Location);

    this->Velocity.x = 0;
    this->Velocity.y = 0;
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

        this->Sprite.setPosition(this->Location);
    }
}

void BaseCharacter::ResetJump()
{
    this->JumpCount = 0;
    this->OnGround  = true;
    this->InJump = false;
}