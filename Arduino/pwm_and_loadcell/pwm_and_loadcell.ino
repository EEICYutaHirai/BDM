#include "HX711.h"

HX711 scale;

//const int A1 = //DAT
//const int A0 = //CLK(たぶんSCK_PIN)
const int M_SW = 5;//モーターのスイッチ
const double STANDARD_VALUE = -35.754020; //キャリブレートして得られた値
const double MIN_WEIGHT = 3000; //モーターが動くときの最小の重さ
const double MAX_WEIGHT = 50000;//想定する最大の重さ

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);

   scale.begin(A1, A0);
   scale.tare();
   scale.set_scale(STANDARD_VALUE);
}

void loop() {
  // put your main code here, to run repeatedly:
  double value = scale.get_units(10);
  if(value<MIN_WEIGHT){
    analogWrite(M_SW,0);
  }else if(value >= MAX_WEIGHT){
    analogWrite(M_SW, 255);
  }
  else{
    analogWrite(M_SW,(value-MIN_WEIGHT)*255/(MAX_WEIGHT-MIN_WEIGHT));
  }
  //100msごとにpwmを更新
  delay(100);
}
