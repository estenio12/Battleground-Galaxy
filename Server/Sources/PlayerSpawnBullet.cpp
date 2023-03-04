#include "../Includes/Player.hpp"

sf::Vector2f Player::CalculateSpawnBullet()
{
    switch (this->BULLET_DIRECTION)
    {
        case INPUT::UP:
            return CalculateSpawnBulletUp();
        break;

        case INPUT::UPLEFT:
            return CalculateSpawnBulletUpLeft();
        break;

        case INPUT::UPRIGHT:
            return CalculateSpawnBulletUpRight();
        break;

        case INPUT::DOWN:
            return CalculateSpawnBulletDown();
        break;

        case INPUT::DOWNLEFT:
            return CalculateSpawnBulletDownLeft();
        break;

        case INPUT::DOWNRIGHT:
            return CalculateSpawnBulletDownRight();
        break;

        case INPUT::LEFT:
            return CalculateSpawnBulletLeft();
        break;

        case INPUT::RIGHT:
            return CalculateSpawnBulletRight();
        break;
    }

    return sf::Vector2f((Location.x + Size.x) ,
                        Location.y + (Size.y / 2));
}

sf::Vector2f Player::CalculateSpawnBulletUp()
{
    sf::Vector2f loc;

    loc.x = Location.x + ((Size.x / 2) - BulletHalfSizeX());
    loc.y = (Location.y - BulletFullSizeY());
    
    return loc;
}

sf::Vector2f Player::CalculateSpawnBulletUpLeft()
{
    sf::Vector2f loc;

    loc.x = Location.x - BulletFullSizeX();
    loc.y = (Location.y - BulletFullSizeY());
    
    return loc;
}

sf::Vector2f Player::CalculateSpawnBulletUpRight()
{
    sf::Vector2f loc;

    loc.x = (Location.x + Size.x) + BulletHalfSizeX();
    loc.y = (Location.y - BulletFullSizeY());
    
    return loc;
}

sf::Vector2f Player::CalculateSpawnBulletDown()
{
    sf::Vector2f loc;

    loc.x = Location.x + ((Size.x / 2) - BulletHalfSizeX());
    loc.y = (Location.y + Size.y) + SAFE_DISTANCE_SPAWN;
    
    return loc;
}

sf::Vector2f Player::CalculateSpawnBulletDownLeft()
{
    sf::Vector2f loc;

    loc.x = Location.x - BulletFullSizeX();
    loc.y = (Location.y + Size.y) + SAFE_DISTANCE_SPAWN;
    
    return loc;
}

sf::Vector2f Player::CalculateSpawnBulletDownRight()
{
    sf::Vector2f loc;

    loc.x = (Location.x + Size.x) + BulletFullSizeX();
    loc.y = (Location.y + Size.y) + SAFE_DISTANCE_SPAWN;
    
    return loc;
}

sf::Vector2f Player::CalculateSpawnBulletLeft()
{
    sf::Vector2f loc;

    loc.x = Location.x - BulletFullSizeX();
    loc.y = Location.y + ((Size.y / 2) - BulletHalfSizeY());
    
    return loc;
}

sf::Vector2f Player::CalculateSpawnBulletRight()
{
    sf::Vector2f loc;

    loc.x = (Location.x + Size.x) + (BulletHalfSizeX() );
    loc.y = Location.y + ((Size.y / 2) - BulletHalfSizeY());

    return loc;
}

float Player::BulletHalfSizeX()
{
    switch (GUNHOLD)
    {
        case GUN::BASIC:
            return BULLET::BASIC_SIZE[0] / 2;
        break;

        case GUN::LASER:
            return BULLET::LASER_SIZE[0] / 2;
        break;

        case GUN::QUANTUNBUBBLE:
            return BULLET::QUANTUMBUBBLE_SIZE[0] / 2;
        break;
    }

    return 0.f;
}

float Player::BulletHalfSizeY()
{
    switch (GUNHOLD)
    {
        case GUN::BASIC:
            return BULLET::BASIC_SIZE[1] / 2;
        break;

        case GUN::LASER:
            return BULLET::LASER_SIZE[1] / 2;
        break;

        case GUN::QUANTUNBUBBLE:
            return BULLET::QUANTUMBUBBLE_SIZE[1] / 2;
        break;
    }

    return 0.f;
}

float Player::BulletFullSizeX()
{
    switch (GUNHOLD)
    {
        case GUN::BASIC:
            return BULLET::BASIC_SIZE[0];
        break;

        case GUN::LASER:
            return BULLET::LASER_SIZE[0];
        break;

        case GUN::QUANTUNBUBBLE:
            return BULLET::QUANTUMBUBBLE_SIZE[0];
        break;
    }

    return 0.f;
}

float Player::BulletFullSizeY()
{
    switch (GUNHOLD)
    {
        case GUN::BASIC:
            return BULLET::BASIC_SIZE[1];
        break;

        case GUN::LASER:
            return BULLET::LASER_SIZE[1];
        break;

        case GUN::QUANTUNBUBBLE:
            return BULLET::QUANTUMBUBBLE_SIZE[1];
        break;
    }

    return 0.f;
}

