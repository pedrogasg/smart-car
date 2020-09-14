#include "PID.h"

namespace pid {

    void PIDController::setupGains(double p, double i, double d)
    {
        this->_Kp = p;
        this->_Ki = i;
        this->_Kd = d;
    }    
    void PIDController::setupOutputRange(double max, double min)
    {
        this->_max = max;
        this->_min = min;
    }
    
    double PIDController::loop(double setPoint, double pointValue)
    {
        double error = setPoint - pointValue;
        
        double out = this->_Kp * error;

        if (out > this->_max)
        {
            out = this->_max;
        } else if (out < this->_min)
        {
            out = this->_min;
        }
        

        return out;

    }
}