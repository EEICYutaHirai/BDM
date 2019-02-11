#include "HX711.h"

HX711 scale;

const int M_SW = 5;//モーターのスイッチ(pwm)
const double STANDARD_VALUE = -35.754020; //キャリブレートして得られた値
const double MIN_WEIGHT = 3000.; //モーターが動くときの最小の重さ
const double MAX_WEIGHT = 10000.;//想定する最大の重さ

const int brake = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(brake, OUTPUT);
   scale.begin(A1, A0);
   scale.tare();
   scale.set_scale(STANDARD_VALUE);
}

void loop() {
  Serial.println("start");
  unsigned long long start = millis();
  for(int i=0;i<1024;i++){
    Serial.println(analogRead(A4));
    }
    unsigned long long end = millis();
    Serial.println((int)(end-start));
    //改行まで読み込む
    String res = Serial.readStringUntil(10);
    //Serial.println(got_string);
    double Ec = res.toFloat();
    //limit pwm
    double limit_value = 255./12.*(5. + Ec);
  // put your main code here, to run repeatedly:
  double value = scale.get_units(10);
  int pwm = 0;
  bool is_brake = false;
  if(value<MIN_WEIGHT){
    pwm = 0;
    analogWrite(M_SW,pwm);
    digitalWrite(brake, HIGH);
    is_brake = true;
  }else if(value >= MAX_WEIGHT){
    pwm = (int)limit_value;
    analogWrite(M_SW, pwm);
    digitalWrite(brake, LOW);
    is_brake = false;
  }
  else{
    digitalWrite(brake, LOW);
    double ideal_value = (value-MIN_WEIGHT)*255/(MAX_WEIGHT-MIN_WEIGHT);
    double pwm_value = limit_value<ideal_value?limit_value:ideal_value;
    pwm = (int)pwm_value;
    analogWrite(M_SW,pwm);
    is_brake = false;
  }
  Serial.println(pwm);
  
  if(is_brake){
    Serial.println("braked");
  }else{
    Serial.println("not braked");
  }
}
