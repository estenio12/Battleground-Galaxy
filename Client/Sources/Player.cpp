#include "../Includes/Player.hpp"

Player::Player(sf::Texture& Texture):Texture(Texture)
{
    this->LoadSprite();
    this->LoadBullet();
    this->LoadTimers();
}

Player::~Player(){}

void Player::Update()
{
    this->Location += this->Velocity;
    this->Sprite.setPosition(this->Location);
    this->UpdateBoundingBox();
    this->BonusAction();

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
    this->BonusRender();

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
    switch (this->Bonus)
    {
        case BONUS::MOVESPEED:
            this->ApplyBonusMovespeed();
        break;

        case BONUS::SHIELD:
            this->ApplyBonusShield();
        break;
    }
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

void Player::ApplyBonusMovespeed()
{
    this->MOVESPEED = BONUS_MOVESPEED;
    this->MovespeedActiveted = true;
    this->Bonus = BONUS::NONE;
}

void Player::ApplyBonusShield()
{
    this->ShieldActiveted = true;
    this->Bonus = BONUS::NONE;
}

void Player::ApplyBonusHPRecover()
{
    this->HPRecoverActiveted = true;
}

void Player::LoadTimers()
{
    MovespeedTimer = new Timer(SYSATTR::BONUS::MOVESPEED_DURATION);
    ShieldTimer    = new Timer(SYSATTR::BONUS::SHIELD_DURATION);
    HPRecoverTimer = new Timer(SYSATTR::BONUS::HPRECOVER_DURATION);
}

void Player::BonusAction()
{
    if(this->MovespeedActiveted)
    {
        std::cout << "Debug MV Antes: " << this->MOVESPEED << std::endl;
        if(this->MovespeedTimer->ExecuteTimer())
        {
            this->MovespeedActiveted = false;
            this->MovespeedTimer->ResetTimer();
            this->MOVESPEED = SYSATTR::DEFAULT::MOVESPEED;
            std::cout << "Debug MV depois: " << this->MOVESPEED << std::endl;
        }
    }

    if(this->ShieldActiveted)
    {
        if(this->ShieldTimer->ExecuteTimer())
        {
            this->ShieldActiveted = false;
            this->ShieldTimer->ResetTimer();
        }
    }
}

void Player::BonusRender()
{
    if(this->ShieldActiveted)
    {
        this->Sprite.setColor(sf::Color::Green);
    }

    if(this->HPRecoverActiveted)
    {
        if(HPRecoverTimer->ExecuteTimer())
        {
            this->HPRecoverActiveted = false;
        }
    }
}

void Player::BonusHandler(char Bonus)
{
    switch(Bonus)
    {
        case BONUS::HPRECOVER:
            this->ApplyBonusHPRecover();
        break;

        default:
            this->Bonus = Bonus;
        break;
    }
}


