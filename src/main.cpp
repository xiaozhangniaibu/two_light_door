#include <Arduino.h>
#include <phyphoxBle.h>
#include <OneButton.h>
OneButton button0(0,true);



unsigned int tn0=0;
unsigned int tn1=0;
unsigned int tn2=0;
double t;
int i =0;
void attachClick0() {
  i = 0;
  digitalWrite(2,HIGH);
}
void interr_1(){
  tn1=micros();
  if(i==0){
    tn0=tn1;
    i=1;
    digitalWrite(2,LOW);
  }
  // Serial.print("tn1:");
  // Serial.println(tn1);
}

void interr_2(){
  tn2=micros();
  // Serial.print("tn2:");
  // Serial.println(tn2);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  PhyphoxBLE::start("phyphox-Arduino");  

  // pinMode(0, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  attachInterrupt(25,interr_1,RISING);

  attachInterrupt(26,interr_2,RISING);
  // button0.attachClick(attachClick0);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("1");
    // button0.tick();

    if(tn1>0 && tn2>0&&tn1<tn2){//
      float v,tn;
      t=tn2-tn1;
      tn=((tn2-tn0)-(t/2))/1000000;
      v=10000/t;
      PhyphoxBLE::write(tn,v);
      // Serial.print("tn1:");
      // Serial.println(tn1);
      // Serial.print("tn2:");
      // Serial.println(tn2);
      Serial.print(tn);
      Serial.print(",");
      Serial.println(v);
      tn1=0;
      tn2=0;
    }

}
