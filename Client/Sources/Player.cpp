#include "../Includes/Player.hpp"

Player::Player(sf::Texture& Texture):Texture(Texture)
{
    this->LoadSprite();
    this->LoadBullet();
}

Player::~Player(){}

void Player::Update()
{
    this->Location += this->Velocity;
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
    const int SPRITE_SIZE = 64;
    Sprite.setTexture(this->Texture);
    Sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
    this->Location = sf::Vector2f(150, 50);
    this->Size = sf::Vector2f(SPRITE_SIZE, SPRITE_SIZE);
    this->Sprite.setPosition(this->Location);
    this->CollisionType = CollisionChannel::BLOCK;
    this->UpdateBoundingBox();
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
        this->IncrementBulletIndex();
    }

    if(FIRE::BONUS == State)
    {
        this->TriggerBonus();
    }
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

    if(Bullet_Index > (MAX_BULLET - 1))
    {
        this->Bullet_Index = 0;
    }
}






