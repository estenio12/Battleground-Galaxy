// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <SFML/Graphics.hpp>

enum CollisionChannel 
{
    NO_COLLISION,
    BLOCK,
    OVERLAP
};

namespace BULLET
{
    static const float BASIC_SIZE[] = {32.f, 32.f};
    static const float LASER_SIZE[] = {64.f, 32.f};
    static const float QUANTUMBUBBLE_SIZE[] = {64.f, 64.f};
}

namespace INPUT
{
    static const char NONE      = '0';
    static const char UP        = '1';
    static const char LEFT      = '2';
    static const char DOWN      = '3';
    static const char RIGHT     = '4';
    static const char UPRIGHT   = '5';
    static const char UPLEFT    = '6';
    static const char DOWNRIGHT = '7';
    static const char DOWNLEFT  = '8';
}

namespace NETCODE_CMD
{
    static const char REPLICATE    = '0';
    static const char UPDATEINFO   = '1';
    static const char DISCONNECTED = '2';
    static const char DEAD         = '3';
    static const char REBORN       = '4';
    static const char BONUS        = '5';
    static const char GUN          = '6';
    static const char KILLNOTIFIER = '7';
}

namespace GUN
{
    static const char BASIC         = '0';
    static const char QUANTUNBUBBLE = '1';
    static const char LASER         = '2';
}

namespace BONUS
{
    static const char NONE      = '0';
    static const char MOVESPEED = '1';
}

namespace FIRE
{
    static const char NONE  = '0';
    static const char FIRE  = '1';
    static const char BONUS = '2';
}