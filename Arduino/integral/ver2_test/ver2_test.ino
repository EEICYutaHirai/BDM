#include "HX711.h"

HX711 scale1;
HX711 scale2;

const int M_SW = 6;                       //モーターのスイッチ(pwm)
const double STANDARD_VALUE = 34.005; //キャリブレートして得られた値
const double MIN_WEIGHT = 500.;           //モーターが動くときの最小の重さ
const double MAX_WEIGHT = 10000.;         //想定する最大の重さ

const int brake = 7;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(brake, OUTPUT);
    scale1.begin(A1, A0);
    scale2.begin(A2,A3);
    scale1.tare();
    scale1.set_scale(STANDARD_VALUE);
    scale2.set_scale(STANDARD_VALUE);
}

unsigned long long start;
unsigned long long end;
int weight1,weight2;
int pwm;
bool is_brake;
int pwm_max = 150;
//scale1が前方,scale2が後方

void loop()
{
    //Serial.println("start");
    //start = millis();
    /*
    for (int i = 0; i < 1024; i++)
    {
        //Serial.println(analogRead(A4));
    }
    */
    //end = millis();
    //Serial.println((int)(end - start));
    weight1 = scale1.get_units(5);
    weight2 = scale2.get_units(5);
    Serial.println("weight forward:"+String(weight1));
    Serial.println("weight backward"+String(weight2));
    //pwm = Serial.readStringUntil(10).toInt();
    //analogWrite(M_SW, pwm);
    //analogWrite(M_SW, 80);
    /*if(weight < MIN_WEIGHT){
        digitalWrite(brake, HIGH);
    }else{
      digitalWrite(brake, LOW);
    }*/
    if(weight1 < 1000 || weight2 < 1000 ||(double)weight1/(double)weight2 < 0.8){
      digitalWrite(brake,HIGH);
      analogWrite(M_SW, 255);
      Serial.println("pwm: 0");
    }else{
      digitalWrite(brake,HIGH);
      analogWrite(M_SW, 255-min(pwm_max, 50 * weight1 / weight2));
      Serial.println("pwm: " + String(min(pwm_max, 10 * weight1 / weight2)));
    }
    Serial.println("");
}
