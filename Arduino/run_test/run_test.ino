#include "HX711.h"

HX711 scale;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  scale.begin(A3,A2);
  scale.tare();
  scale.set_scale(-97823./2736.);
}

double weight;
double MAX_WEIGHT = 40000.;
double MIN_WEIGHT = 15000.;
int pwm;
//int tstart,tend;
void loop() {
  // put your main code here, to run repeatedly:
  //tstart = millis();
  weight = scale.get_units(5);
  if(weight > MAX_WEIGHT){
    pwm = 255;  
  }else if(weight > MIN_WEIGHT){
    pwm = 255. * (weight - MIN_WEIGHT)/(MAX_WEIGHT-MIN_WEIGHT);  
  }else{
    pwm = 0;  
  }
  //Serial.println(pwm);
  analogWrite(6,pwm);
  //Serial.println(millis()-tstart);
}
