// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../Helpers/Definitions.hpp"
#include "../Helpers/SystemAttributes.hpp"
#include "../Includes/BaseCharacter.hpp"
#include "../Includes/Bullet.hpp"
#include "../Includes/Timer.hpp"

class Player : public BaseCharacter
{
    public:
        char PID;
        std::string IP;
        unsigned short PORT; 

    public:
        const float MAX_HP = SYSATTR::DEFAULT::MAX_HP; 
        float HP           = MAX_HP;
        char GUNHOLD       = GUN::BASIC;
        char Bonus         = BONUS::NONE;
        bool IsDead        = false;
        bool IsReborn      = false;
        bool Disconnected  = false;

    public:
        std::vector<Bullet*> BulletList;

    private:
        const int MAX_BULLET = 30;
        const float SAFE_DISTANCE_SPAWN = 10.f;
        int Bullet_Index = 0;
        const float BONUS_MOVESPEED = SYSATTR::DEFAULT::MOVESPEED + 
                                      SYSATTR::DEFAULT::BONUS_MOVESPEED;

    private:
        bool MovespeedActiveted = false;
        bool ShieldActiveted    = false;
        bool HPRecoverActiveted = false;
        Timer* MovespeedTimer;
        Timer* ShieldTimer;
        Timer* HPRecoverTimer;
        Timer* RebornTimer;

    public:
        Player(char PID,
               std::string IP,
               unsigned short PORT);
        ~Player();

    private:
        void LoadPlayer();
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
        void ApplyDamage(float );
        
    public:
        void TriggerFire(char );
        void TriggerBonus();
        void CallReborn();
        std::shared_ptr<std::string> GetStrHP();
        std::shared_ptr<std::string> GetStrLocation();

    public:
        void NetInputProcess(std::shared_ptr<std::string> Input);
    
    private:
        void NetReplicante(std::shared_ptr<std::string> );
        void NetDisconnect();

    private:
        void BonusHandler(char );
        void ApplyBonusMovespeed();
        void ApplyBonusHPRecover();
        void ApplyBonusShield();
        void LoadTimers();
        void BonusAction();
        void BonusRender();
        void DeathHandler();

    private:
        int ConvertToInt(std::string Value);
        float ConvertToFloat(std::string Value);
        std::shared_ptr<std::string> Substring(std::string Target, 
                                               int start, 
                                               int end);
        std::vector<float> GetLocation(std::string );
};