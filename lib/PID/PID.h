#ifndef PID_H
#define PID_H
namespace pid {
    class PIDController
    {
    private:
        /* data */
    
    public:
        PIDController(double p, double i, double d, double max, double min)
        {
            setup(p,i,d,max,min);
        };
        PIDController(){};
        ~PIDController() = default;

        void setup(double p, double i, double d, double max, double min)
        {
            setupGains(p,i,d);
            setupOutputRange(max,min);
        }

        void 
            setupGains(double p, double i, double d),
            setupOutputRange(double max, double min);
        
        double 
            loop(double setPoint, double pointValue);
    private:
        double
            _Kp,
            _Ki,
            _Kd,
            _max,
            _min;
    
    };       
}

#endif
