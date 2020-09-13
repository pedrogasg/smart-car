#include <Arduino.h>
#include <HBridgeController.h>

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

h_bridge_controller::Motor* leftMotor  = new h_bridge_controller::Motor();
h_bridge_controller::Motor* rigthMotor  = new h_bridge_controller::Motor();

h_bridge_controller::Encoder* leftEncoder = new h_bridge_controller::Encoder();
h_bridge_controller::Encoder* rigthEncoder = new h_bridge_controller::Encoder();

IntervalTimer myTimer;

void ISR_timerone(void)
{
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
    int speed = Serial.parseInt();
    if (speed >= 189 && speed <= 255)
    {
      leftMotor->setVoltage(speed, false);
      rigthMotor->setVoltage(speed, false);
    }

  }
}
 
