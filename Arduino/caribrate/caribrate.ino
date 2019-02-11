#include "HX711.h"

HX711 scale;

//const int A1 = 14;//DAT
//const int A0 = PIN_A0;//CLK(たぶんSCK_PIN)

//proto type 1 
//front calibration value 2764578.00 (g) scale.begin(A2,A3)
//rear calibration value 2149069.00 (g) scale.begin(A1,A0)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //scale.begin(DAT,SCK);
  scale.begin(A1,A0);
  //scale.begin(A2,A3);
  //初期状態では何も載せてはいけない
  scale.set_scale();
  scale.tare();

  Serial.println("Put something");
  //500gのものを置いたとする
  //new loadcell
  double weight = 65000.;
  delay(5000);
  double value = scale.get_units(10);
  Serial.println(value);
  //-97823(これが実験値)
  //double value=2210345.00; // new loadcell
  scale.set_scale(value/weight);
}

void loop() {
  // put your main code here, to run repeatedly:
  //既知の重さの何かを乗せる。
  //scale.get_unit(10) の値をその重さで割る。(単位重さあたりの値)
  //今回はグラムを単位としよう
  //この割った値を、以後常にscale.set_scaleの引数に入れる必要がある。
  //きゃりぶれーとすると, get_unit(n) で重さがわかる。nは直近何回の平均を取るか。
  Serial.println(scale.get_units(1));
  delay(1000);
}
