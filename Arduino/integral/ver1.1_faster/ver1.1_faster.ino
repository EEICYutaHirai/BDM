#include "HX711.h"

HX711 scale;

const int M_SW = 5;                       //モーターのスイッチ(pwm)
const double STANDARD_VALUE = -35.754020; //キャリブレートして得られた値
const double MIN_WEIGHT = 500.;           //モーターが動くときの最小の重さ
const double MAX_WEIGHT = 10000.;         //想定する最大の重さ

const int brake = 7;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(brake, OUTPUT);
    scale.begin(A1, A0);
    scale.tare();
    scale.set_scale(STANDARD_VALUE);
}

unsigned long long start;
unsigned long long end;
int weight;
int pwm;
bool is_brake;

void loop()
{
    Serial.println("start");
    start = millis();
    for (int i = 0; i < 1024; i++)
    {
        //Serial.println(analogRead(A4));
    }
    end = millis();
    Serial.println((int)(end - start));
    weight = scale.get_units(10);
    Serial.println(weight);
    pwm = Serial.readStringUntil(10).toInt();
    //analogWrite(M_SW, pwm);
    analogWrite(M_SW, 80);
    if(weight < MIN_WEIGHT){
        digitalWrite(brake, HIGH);
    }else{
      digitalWrite(brake, LOW);
    }
}
