// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

#include "../Helpers/Definitions.hpp"
#include "../Helpers/SystemAttributes.hpp"
#include "../Includes/BaseCharacter.hpp"
#include "../Includes/Bullet.hpp"
#include "../Includes/Timer.hpp"

#define pout(x) std::cout << x << std::endl

class Player : public BaseCharacter
{
    private:
        sf::Texture Texture;
        sf::RectangleShape HPBar;
        sf::RectangleShape HPBarrier;

    public:
        char PID;
        std::string Nickname = "UNDEFINED";

    public:
        const float MAX_HP = 100; 
        float HP           = 100;
        char GUNHOLD       = GUN::BASIC;
        char Bonus         = BONUS::MOVESPEED;
        bool IsDead        = false;
        bool Disconnected  = false;

    public:
        std::vector<Bullet*> BulletList;

    private:
        const int MAX_BULLET = 30;
        const float SAFE_DISTANCE = 10.f;
        int Bullet_Index = 0;
        const float BONUS_MOVESPEED  = SYSATTR::DEFAULT::MOVESPEED + 
                                       SYSATTR::DEFAULT::BONUS_MOVESPEED;
        const float HPBarrierSize = 63.f;

    private:
        bool MovespeedActiveted = false;
        bool ShieldActiveted    = false;
        bool HPRecoverActiveted = false;
        Timer* MovespeedTimer;
        Timer* ShieldTimer;
        Timer* HPRecoverTimer;

    public:
        Player(sf::Texture& );
        ~Player();

    private:
        void LoadSprite();
        void LoadHUD();
        void JumpAndGravity();
        void LoadBullet();
        void IncrementBulletIndex();
        float BulletHalfSizeX();
        float BulletHalfSizeY();
        float BulletFullSizeX();
        float BulletFullSizeY();
        sf::Vector2f CalculateSpawnBullet();
        sf::Vector2f CalculateSpawnBulletUp();
        sf::Vector2f CalculateSpawnBulletDown();
        sf::Vector2f CalculateSpawnBulletLeft();
        sf::Vector2f CalculateSpawnBulletRight();
        sf::Vector2f CalculateSpawnBulletUpLeft();
        sf::Vector2f CalculateSpawnBulletUpRight();
        sf::Vector2f CalculateSpawnBulletDownLeft();
        sf::Vector2f CalculateSpawnBulletDownRight();

    public:
        void Update() override;
        void Render(sf::RenderWindow* ) override;

    public:
        void TriggerFire(char );
        void TriggerBonus();
        void CallReborn();
        void SetHPColor(const sf::Color);
        void ApplyDeath();

    public:
        void NetInputProcess(std::shared_ptr<std::string> Input);
    
    private:
        void NetReplicante(std::shared_ptr<std::string> );
        void NetUpdateInfo(std::shared_ptr<std::string> );
        void NetActiveBonus(std::shared_ptr<std::string> );
        void NetActiveGun(std::shared_ptr<std::string> );
        void NetDamage(std::shared_ptr<std::string> );
        void NetDisconnect();
        void NetDeath();
        void NetReborn();

    private:
        void BonusHandler(char );
        void ApplyBonusMovespeed();
        void ApplyBonusHPRecover();
        void ApplyBonusShield();
        void LoadTimers();
        void BonusAction();
        void BonusRender();

    private:
        void UpdateHUD();
        void RenderHUD(sf::RenderWindow* );
        void ApplyDamage(float );

    private:
        int ConvertToInt(std::string Value);
        int ConvertToInt(char Value);
        float ConvertToFloat(std::string Value);
        std::shared_ptr<std::string> Substring(std::string Target, 
                                               int start, 
                                               int end);
        std::vector<float> GetLocation(std::string );
};