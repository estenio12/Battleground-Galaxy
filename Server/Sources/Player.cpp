#include "../Includes/Player.hpp"

Player::Player(char PID,
               std::string IP,
               unsigned short PORT):
               PID(PID),
               IP(IP),
               PORT(PORT)
{
    this->LoadPlayer();
    this->LoadBullet();
}

Player::~Player()
{
    BulletList.clear();
}

void Player::Update()
{
    this->Location += Velocity;
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

void Player::LoadPlayer()
{
    this->Location = sf::Vector2f(150, 50);
    this->Size = sf::Vector2f(64, 64);
    this->CollisionType = CollisionChannel::BLOCK;
    this->UpdateBoundingBox();
}

void Player::LoadBullet()
{
    for(int i = 0; i < MAX_BULLET; i++)
    {
        auto temp = new Bullet();
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
        if(this->MovespeedTimer->ExecuteTimer())
        {
            this->MovespeedActiveted = false;
            this->MovespeedTimer->ResetTimer();
            this->MOVESPEED = SYSATTR::DEFAULT::MOVESPEED;
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

std::shared_ptr<std::string> Player::GetStrHP()
{
    std::string strHP    = std::to_string((int)this->HP);
    std::string strFinal = "";

    for(int i = strHP.size(); i < 3; i++)
    {
        strFinal.push_back('0');
    }

    strFinal += strHP;

    return std::make_shared<std::string>(strFinal);
}

std::shared_ptr<std::string> Player::GetStrLocation()
{
    std::string x = std::to_string(this->Location.x);
    std::string y = std::to_string(this->Location.y);

    return std::make_shared<std::string>(x + "|" + y);
}