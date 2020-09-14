#include <Arduino.h>
#include <SmartCar.h>

#define OUTPUT_MIN 180
#define OUTPUT_MAX 255
#define KP 2
#define KI .4
#define KD 0

int Hz=10;
int setPoint = 0;
int speed1, speed2;
int output_bits = 8;
bool output_signed = false;

int voltage = 155;
int aceletation = 0;

int error;
float Kp = 1.0;
int setPoint;


smart_car::Motor* leftMotor  = new smart_car::Motor();
smart_car::Motor* rigthMotor  = new smart_car::Motor();

smart_car::Encoder* leftEncoder = new smart_car::Encoder();
smart_car::Encoder* rigthEncoder = new smart_car::Encoder();

IntervalTimer myTimer;

void ISR_timerone(void)
{
  error = setPoint - speed1;
  int increment = 0;
  if(error > 0){
    increment = Kp * error;
    if(increment > 100){
      increment = 100;
    }
  }
  aceletation += increment;
  speed1 = leftEncoder->lap();
  speed2 = rigthEncoder->lap();
  Serial.print("Motor Speed 1: ");
  Serial.print(speed1);
  Serial.print(" / ");
  Serial.print("Motor Speed 2: "); 
  Serial.print(speed2);
  Serial.println();
  
}

void setup()
{
  myTimer.begin(ISR_timerone, 1000000);

  leftMotor->setup(15, 13, 14);
  rigthMotor->setup(10, 11, 12);
  leftEncoder->setup(23, []{ leftEncoder->count();}, 5);
  rigthEncoder->setup(22, []{ rigthEncoder->count();}, 5);
    
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
  Serial.println("But the advice 50 to 255. Because the minimum voltage required to start the motor is 50.");

}
 
void loop()
{
  if (Serial.available())
  {
    setPoint = Serial.parseInt();
    if (setPoint >= 189 && setPoint <= 255)
    {
      leftMotor->setVoltage(voltage + aceletation, false);
      rigthMotor->setVoltage(0, false);
    }

  }
}
 
