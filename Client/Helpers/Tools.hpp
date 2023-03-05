// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

#include <vector>
#include <string>

namespace Tools
{
    static const std::vector<std::string> Split(std::string Value, char Target)
    {
        std::vector<std::string> Temp;
        std::string TempItem = "";

        for(int i = 0; i < Value.size(); i++)
        {
            if(Value[i] == Target)
            {
                Temp.push_back(TempItem);
                TempItem.clear();
            }
            else
            {
                TempItem.push_back(Value[i]);
            }
        }

        if(!TempItem.empty())
        {
            Temp.push_back(TempItem);
            TempItem.clear();
        }

        return Temp;
    }
}