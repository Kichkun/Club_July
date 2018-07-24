#include <Wire.h>
#include <Multiservo.h>
 
Multiservo S1;
Multiservo S2;
int incomingByte=0;
void setup(void)
{
  Serial.begin(9600);
  S1.attach(12);
  S2.attach(5);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  S1.write(90);
  S1.write(90);
}
 
void loop()
{
    if (Serial.available() > 0) {  //если есть доступные данные
        // считываем байт
        incomingByte = Serial.read();
 
        // отсылаем то, что получили
        Serial.print("I received: ");
        Serial.println(incomingByte,DEC);
    }
    if(incomingByte == 111)RVO();
    if(incomingByte == 110)RVC();
    if(incomingByte == 101)LVO();
    if(incomingByte == 100)LVC();
    if(incomingByte == 120){RVO();LVO();}
    if(incomingByte == 121){RVC();LVC();}
    switch(incomingByte)
    {
    case '111':
        RVO();
    break;
    
    case 110:
        RVC();
    break;   
    
    case 101:
        LVO();
    break;
    
    case 100:
        LVC();
    break;
    
    case 120:
        LVO();
        RVO();
    break;
    
    case 121:
        LVC();
        RVC();
    break; 
    }
  }

void RVO()
{
  if (digitalRead(2) == 0) S1.write(90);else S1.write(0);
}
void RVC()
{
  if (digitalRead(3) == 0) S1.write(90);else S1.write(180);
}
void LVO()
{
  if (digitalRead(4) == 0) S2.write(90);else S2.write(0);
}
void LVC()
{
  if (digitalRead(5) == 0) S2.write(90);else S2.write(180);
}
