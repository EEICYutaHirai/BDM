
void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  //pinMode(A0,INPUT);
  Serial.begin(115200);
}
void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(5,90);
  Serial.println("start");
  unsigned long long start = millis();
  for(int i=0;i<1024;i++){
    Serial.println(analogRead(A0));
    }
    unsigned long long end = millis();
    Serial.println((int)(end-start));
    //改行まで読み込む
    String res = Serial.readStringUntil(10);
    //Serial.println(got_string);
    double Ec = res.toFloat();
}
