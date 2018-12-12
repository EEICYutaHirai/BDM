#include "HX711.h"

HX711 scale;

//const int A1 = 14;//DAT
//const int A0 = PIN_A0;//CLK(たぶんSCK_PIN)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  scale.begin(A1, A0);
  //初期状態では何も載せてはいけない
  scale.set_scale();
  scale.tare();
}

void loop() {
  // put your main code here, to run repeatedly:
  //既知の重さの何かを乗せる。
  //scale.get_unit(10) の値をその重さで割る。(単位重さあたりの値)
  //今回はグラムを単位としよう
  //この割った値を、以後常にscale.set_scaleの引数に入れる必要がある。
  //きゃりぶれーとすると, get_unit(n) で重さがわかる。nは直近何回の平均を取るか。
  Serial.println(scale.get_units(10));
  delay(1000);
}
