#include <Arduino.h>
#include <PID.h>
#include <SmartCar.h>

int setPoint = 0;
int speed1, speed2;

int voltage = 155;
volatile int acceleration1 = 0;
volatile int acceleration2 = 0;

pid::PIDController* p = new pid::PIDController(.5,0,0,100,-100);

smart_car::Motor* leftMotor  = new smart_car::Motor();
smart_car::Motor* rigthMotor  = new smart_car::Motor();

smart_car::Encoder* leftEncoder = new smart_car::Encoder();
smart_car::Encoder* rigthEncoder = new smart_car::Encoder();

IntervalTimer myTimer;
void ISR_timerone(void)
{
  
  speed1 = leftEncoder->lap();
  speed2 = rigthEncoder->lap();
  acceleration1 += p->loop(setPoint, speed1);
  acceleration2 += p->loop(setPoint, speed1);
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
  leftEncoder->setup(22, []{ leftEncoder->count();}, 5);
  rigthEncoder->setup(23, []{ rigthEncoder->count();}, 5);
    
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
  Serial.println("But the advice 50 to 255. Because the minimum voltage required to start the motor is 50.");

}

void loop()
{
  int v1 = 0;
  int v2 = 0;
  if (Serial.available())
  {
    setPoint = Serial.parseInt();
  }
  if(setPoint > 59){
    v1 = acceleration1 + voltage;
    v2 = acceleration2 + voltage;
  }
  leftMotor->setVoltage(v1, false);
  rigthMotor->setVoltage(v2, false);
  
}
 
