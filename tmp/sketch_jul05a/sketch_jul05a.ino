

#include <Servo.h>

Servo m1;
Servo m2;
int sun;
int sun1;
int sun2;
int sun3;

void stopm1(){
  m1.writeMicroseconds(1000);
  
}

void stopm2(){
  m2.writeMicroseconds(1000);
  
}

void right(){
  m1.writeMicroseconds(1800);
}
void left(){
  m2.writeMicroseconds(1800);
}
void setup() {
  m1.attach(11);
  m2.attach(10);
  
Serial.begin(9600);
}
void stable(){
  m1.writeMicroseconds(1800);
  m2.writeMicroseconds(1800);
}
int numb;

void loop() {
  sun = analogRead(A0);
  sun1 = analogRead(A1);
  sun2 = analogRead(A2);
  sun3 = analogRead(A3);
  int arr[] ={sun, sun1, sun2, sun3};
  int k = min(min(sun, sun1), min(sun2, sun3));
  
  for(int i = 0; i < 4; i++){
    if(k == arr[i]){
      numb = i;
    }
  }
  Serial.print("_________numb ");
  Serial.println(numb);
  //Serial.println(numb);
  if(numb == 0){
     stable();
     Serial.println("stable");
  }
  else if(numb == 1){
    if(sun>k+10){
     right();
     Serial.print("1 ");
     Serial.println(sun);
     sun = analogRead(A0);
     delay(1);
    }
    else{
    stable();
    Serial.println("stable 1");
    }
    
  }
  else if(numb = 3){
    if(sun>k+10){
     left();
     Serial.print("3 ");
     Serial.println(sun);
     sun = analogRead(A0);
     delay(1);
    }
    
    else{
      stable();  
      Serial.println("stable 3");
    }
    
  }
  else if (numb == 2){
    Serial.print("back ");
    if(sun>k+10){
     left();
     Serial.print("back ");
     Serial.println(sun);
     sun = analogRead(A0);
    }
    else{
    stable();
    }
  }
  delay(20);
  
}
