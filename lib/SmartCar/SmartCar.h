#ifndef SMARTCAR_H
#define SMARTCAR_H
namespace smart_car
{
    class Encoder
    {
    private:             
        
    public:
        Encoder(){};
        ~Encoder() = default;
        
        void
            count(void),
            setup(unsigned int irq_pin, void (*ISR_callback)(void), unsigned int delay);

        int
            lap(void);

    private:
        unsigned int 
            _delay,
            _counter = 0;

        unsigned long 
            _last = 0,
            _current;
        
        void
            (*ISR_callback)();
    };

    class Motor
    {
    private:
        
    public:
        Motor(int enable, int input1, int input2)
        {
            setup(enable, input1, input2);
        }
        Motor(){}
        ~Motor() = default;

        void
            setup(int enable, int input1, int input2),
            setVoltage(int speed, bool reverse);

    private:
        int 
            _enable,
            _input1,
            _input2;
    };

    class SmartCar
    {
    private:
        void
            setMotor(int enable, int input1, int input2),
            setEncoder(int encoder);
        /* data */
    public:
        SmartCar(/* args */);
        ~SmartCar() = default;

        void
            setLeftEncoder(int leftEncoder),
            setLeftMotor(int leftEn, int leftIn1, int leftiIn2),

            setRigthEncoder(int rightEncoder),
            setRigthMotor(int rightEn, int rightIn1, int rightIn2);

    private:
        Motor 
            leftMotor,
            rigthMotor;
        
        Encoder
            leftEncoder,
            rigthEncoder;
        
        
    };
    
}
#endif
