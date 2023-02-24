// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "../Includes/Player.hpp"

class RetArgPro
{
    public:
        std::vector<Player*> PlayerList;
};

class ArgumentProcess
{
    public:
        static RetArgPro* Process(std::string );
        static std::vector<std::string> Split(std::string, char );
};