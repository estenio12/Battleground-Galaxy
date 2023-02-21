#include "../Includes/Player.hpp"

Player::Player(sf::Texture& Texture):Texture(Texture)
{
    this->LoadSprite();
    this->LoadBullet();
}

Player::~Player(){}

void Player::Update()
{
    this->JumpAndGravity();
    this->Sprite.setPosition(this->Location);
    this->UpdateBoundingBox();

    // # Update Bullet
    for(auto bullet : BulletList)
    {
        if(bullet->Active)
        {
            bullet->Update();
        }
    }
}

void Player::Render(sf::RenderWindow* Render)
{
    Render->draw(this->Sprite);

    // # Render Bullet
    for(auto bullet : BulletList)
    {
        if(bullet->Active)
        {
            bullet->Render(Render);
        }
    }
}

void Player::LoadSprite()
{
    Sprite.setTexture(this->Texture);
    Sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    this->Location = sf::Vector2f(150, 50);
    this->Size = sf::Vector2f(64, 64);
    this->Sprite.setPosition(this->Location);
    this->CollisionType = CollisionChannel::BLOCK;
    this->UpdateBoundingBox();
}

void Player::JumpAndGravity()
{
    this->Velocity.y += 3.8f;

    if(InJump)
    {
        Velocity.y = -(10.1 * 3.8f * (3.8f - 1) * DELTATIME);
        InJump = false;
    }

    this->Location += this->Velocity;
}

void Player::LoadBullet()
{
    for(int i = 0; i < MAX_BULLET; i++)
    {
        auto temp = new Bullet(this->Texture);
        this->BulletList.push_back(temp);
    }
}

void Player::TriggerFire(char State)
{
    if(FIRE::FIRE == State)
    {
        BulletList[Bullet_Index]->SetActive(CalculateSpawnBullet(),
                                            BULLET_DIRECTION,
                                            GUNHOLD);
    }

    if(FIRE::BONUS == State)
    {
        this->TriggerBonus();
    }

    this->IncrementBulletIndex();
}

void Player::TriggerBonus()
{
    
}

void Player::CallReborn()
{
    HP      = MAX_HP;
    GUNHOLD = GUN::BASIC;
    IsDead  = false;
}

void Player::IncrementBulletIndex()
{
    this->Bullet_Index++;

    if(Bullet_Index > MAX_BULLET)
    {
        this->Bullet_Index = 0;
    }
}

sf::Vector2f Player::CalculateSpawnBullet()
{
    sf::Vector2f loc;
    float SAFE_DISTANCE = 10.f;

    switch (this->BULLET_DIRECTION)
    {
        case INPUT::RIGHT:
            loc.x = (Location.x + Size.x) + SAFE_DISTANCE;
            loc.y = CalculateSpawnBulletY();
        break;

        case INPUT::LEFT:
            loc.x = (Location.x - CalculateSpawnBulletX()) - SAFE_DISTANCE;
            loc.y = CalculateSpawnBulletY();
        break;
    }

    return loc;
}

float Player::CalculateSpawnBulletY()
{
    switch (this->GUNHOLD)
    {
        case GUN::BASIC:
            return (Location.y + (Size.y / 2)) - (BULLET::BASIC_SIZE[1] / 2);
        break;

        case GUN::LASER:
            return (Location.y + (Size.y / 2)) - (BULLET::LASER_SIZE[1] / 2);
        break;

        case GUN::QUANTUNBUBBLE:
            return (Location.y + (Size.y / 2)) - (BULLET::QUANTUMBUBBLE_SIZE[1] / 2);
        break;
    }

    return (Location.y + (Size.y / 2));
}

float Player::CalculateSpawnBulletX()
{
    switch (this->GUNHOLD)
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

    return BULLET::BASIC_SIZE[0];
}

