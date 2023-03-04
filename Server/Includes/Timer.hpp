// # 
// # Copyright All (C) 
// # This project was licensed under MIT
// # @author: Estenio Garcia
// # 

#pragma once

class Timer
{
    private:
        float FixedDeltaTime = 0.016;
        float TargetTime = 0.f;
        float CurrentCounter = 0;

    public:
        // # @param TargetTime= Max limit time
        Timer(float TargetTime): TargetTime(TargetTime){}

        void ResetTimer()
        {
            this->CurrentCounter = 0;
        }

        bool ExecuteTimer()
        {
            if(this->CurrentCounter < this->TargetTime)
            {
                this->CurrentCounter += this->FixedDeltaTime;
            }
            else
            {
                return true;
            }

            return false;
        }
};