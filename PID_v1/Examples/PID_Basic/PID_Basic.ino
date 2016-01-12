/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>
#include <MAX6675.h>
// #include <Time.h>

//  CS SO SCK
MAX6675 max6675(12,13,11,1);

float heater_value = 0.f;
float motor_value = 0.f;

int temperature = 0;

int pot_pin_motor = 0;
int pot_val_motor = 0;

int pot_pin_heater = 1;
int pot_val_heater = 0;

int pot_motor_enabled = 1;
int pot_heater_enabled = 1;

int pin_pwm_motor = 9;
int pin_pwm_heater = 10;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

void setup()
{
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = 50;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void updatePID(){
   pidInput = t2;
   myPID.SetTunings(pidP,pidI,pidD);
   myPID.Compute();
   setPowerLevel(pidOutput); // range set in setup to 0 - 100%
}

void loop()
{
  Input = analogRead(0);
  myPID.Compute();

  analogWrite(pin_pwm_motor,250/2);
}


