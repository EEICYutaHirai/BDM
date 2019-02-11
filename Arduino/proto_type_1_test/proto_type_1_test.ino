#include "HX711.h"

HX711 front_load_cell;
HX711 rear_load_cell;

const int MOTOR_PIN = 6;
const int BREAK_PIN = 7;
const double MIN_WEIGHT = 5000.;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  front_load_cell.begin(A2,A3);
  rear_load_cell.begin(A1,A0);
  front_load_cell.tare();
  rear_load_cell.tare();
  front_load_cell.set_scale(2764578./65000.);
  rear_load_cell.set_scale(2149069./65000.);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BREAK_PIN, OUTPUT);
}

double current_front_weight;
double current_rear_weight;
double front_rear_rate;

void loop() {
  // put your main code here, to run repeatedly:
  current_front_weight = front_load_cell.get_units(1);
  current_rear_weight = rear_load_cell.get_units(1);
  front_rear_rate = current_front_weight / current_rear_weight;
  Serial.println("front: "+String(current_front_weight));
  Serial.println("rear: "+String(current_rear_weight));
  
  //Low ->   brake

  if(current_front_weight < MIN_WEIGHT || current_rear_weight<MIN_WEIGHT || front_rear_rate < 0.5){
    digitalWrite(BREAK_PIN,LOW);
    analogWrite(MOTOR_PIN,255);  
  }else if(front_rear_rate > 3.){
    digitalWrite(BREAK_PIN,HIGH);
    analogWrite(MOTOR_PIN,0);
  }
  else{
      digitalWrite(BREAK_PIN,HIGH);
      analogWrite(MOTOR_PIN, 255.-255./2.7*(front_rear_rate-0.3));
  }
}
