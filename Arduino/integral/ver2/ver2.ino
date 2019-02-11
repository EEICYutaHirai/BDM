#include "HX711.h"

HX711 scale1;
HX711 scale2;

const int M_SW = 6;                       //モーターのスイッチ(pwm)
const double STANDARD_VALUE = -35.754020; //キャリブレートして得られた値
const double MIN_WEIGHT = 5000.;           //モーターが動くときの最小の重さ
const double MAX_WEIGHT = 70000.;         //想定する最大の重さ

const int brake = 7;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(brake, OUTPUT);
    scale1.begin(A1, A0);
    scale2.begin(A3,A2);
    //scale1.tare();
    scale1.set_scale(STANDARD_VALUE);
    scale2.set_scale(STANDARD_VALUE);
}

unsigned long long start_time;
unsigned long long end_time;
//weight1 が前
int weight1,weight2;
int pwm;
bool is_brake;

void loop()
{
    Serial.println("start");
    start_time = millis();
    for (int i = 0; i < 1024; i++)
    {
        Serial.println(analogRead(A4));
    }
    end_time = millis();
    Serial.println((int)(end_time - start_time));
    weight1 = scale1.get_units(3);
    weight2 = scale2.get_units(3);
    Serial.println(weight1);
    Serial.println(weight2);
    pwm = Serial.readStringUntil(10).toInt();
    analogWrite(M_SW, pwm);
    //analogWrite(M_SW, 80);
    //LOW=> break, HIGH => not break
    if((double)weight1/(double)weight2 < 0.8){
        digitalWrite(brake, LOW);
        analogWrite(M_SW, 255);
    }else{
      digitalWrite(brake, HIGH);
    }
}
