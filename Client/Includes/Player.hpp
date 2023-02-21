// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../Helpers/Definitions.hpp"
#include "../Includes/BaseCharacter.hpp"
#include "../Includes/Bullet.hpp"

class Player : public BaseCharacter
{
    private:
        sf::Texture Texture;

    public:
        char PID;
        std::string Nickname = "UNDEFINED";

    public:
        const float MAX_HP = 100; 
        float HP           = MAX_HP;
        char GUNHOLD       = GUN::BASIC;
        char Bonus         = BONUS::NONE;
        bool IsDead        = false;
        bool Disconnected  = false;

    public:
        std::vector<Bullet*> BulletList;

    private:
        const int MAX_BULLET = 30;
        int Bullet_Index = 0;

    public:
        Player(sf::Texture& );
        ~Player();

    private:
        void LoadSprite();
        void JumpAndGravity();
        void LoadBullet();
        void IncrementBulletIndex();
        sf::Vector2f CalculateSpawnBullet();
        float CalculateSpawnBulletY();
        float CalculateSpawnBulletX();

    public:
        void Update() override;
        void Render(sf::RenderWindow* ) override;

    public:
        void TriggerFire(char );
        void TriggerBonus();
        void CallReborn();

    public:
        void NetInputProcess(std::shared_ptr<std::string> Input);
    
    private:
        void NetReplicante(std::shared_ptr<std::string> );
        void NetUpdateInfo(std::shared_ptr<std::string> );
        void NetActiveBonus(std::shared_ptr<std::string> );
        void NetActiveGun(std::shared_ptr<std::string> );
        void NetDisconnect();
        void NetDeath();
        void NetReborn();

    private:
        int ConvertToInt(std::string Value);
        int ConvertToInt(char Value);
        float ConvertToFloat(std::string Value);
        std::shared_ptr<std::string> Substring(std::string Target, 
                                               int start, 
                                               int end);
        std::vector<float> GetLocation(std::string );
};