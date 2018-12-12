#include "HxX711.h"

HX711 scale;

//const int A1 = //DAT
//const int A0 = //CLK(たぶんSCK_PIN)
//const int M_SW = //モーターのスイッチ
//const double STANDARD_VALUE = //キャリブレートして得られた値
//const double MIN_WEIGHT = //モーターが動くときの最小の重さ
//const double MAX_WEIGHT = //想定する最大の重さ

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);

   scale.begin(A1, A0);
   scale.set_scale(STANDARD_VALUE);
   //オフセット
   sacale.tare();
}

void loop() {
  // put your main code here, to run repeatedly:
  double value = get_units(10);
  if(value<MIN_WEIGHT){
    analogWrite(M_SW,0);
  }else if(value >= MAX_WEIGHT){
    analogWrite(M_SW, 255);
  }
  else{
    analogWrite(M_SW,(value-MIN_WEIGHT)*255/(MAX_WEIGHT=MIN_WEIGHT));
  }
  //100msごとにpwmを更新
  delay(100);
}
