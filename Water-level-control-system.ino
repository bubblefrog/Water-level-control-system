//P1.0
//I1.0
//D1.0
//S2.0
//U2.6
//PID-C100-S
//M30
//DON-DOFF


#include <FastPID.h>
#include <EEPROM.h>
#include <TimerOne.h>
#define EP_VERSION 1

struct Settings {
  int EPVERSION;
  
  float kP;
  float kI;
  float kD;

  float setpoint;
  float minThr;

  
};

Settings settings;
int output_bits = 8;
bool output_signed = false;
int hz = 10;
FastPID myPID(0, 0, 0, hz, output_bits, output_signed);


float getLevel(){
}


void runPid(){
  uint8_t out = myPID.step(settings.setpoint,getLevel());
  analogWrite(9,out);
}

void setup() {

EEPROM.get(0,settings);
  if (settings.EPVERSION!=EP_VERSION){
    settings = {
      EP_VERSION,
      1.0f,
      1.0f,
      0.0f,
      0.3f
    };
    EEPROM.put(0,settings);
  }

  myPID.setCoefficients(settings.kP,settings.kI,settings.kD,hz);

  Timer1.initialize(100000);
  Timer1.attachInterrupt(runPid);
}

void loop() {
  
  
}
