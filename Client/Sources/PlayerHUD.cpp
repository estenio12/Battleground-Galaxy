#include "../Includes/Player.hpp"

void Player::UpdateHUD()
{
    if(!this->IsDead)
    {
        HPBar.setPosition(Location.x, Location.y - 15.f);
        HPBarrier.setPosition(Location.x + 1, Location.y - 14);
    }
}

void Player::RenderHUD(sf::RenderWindow* Render)
{
    if(!this->IsDead)
    {
        Render->draw(HPBar);
        Render->draw(HPBarrier);
    }
}

void Player::ApplyDamage(float NewHP)
{
    this->HP = NewHP;
    float value = HPBarrierSize * NewHP / MAX_HP;
    this->HPBarrier.setSize(sf::Vector2f(value, 10));
}