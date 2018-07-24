#include <Wire.h> 
#include <TroykaIMU.h> 
#include <Multiservo.h> 

Multiservo S1; 
Multiservo S2; 
int incomingByte=0; 
#define BETA 0.22 
Madgwick filter; 
Accelerometer accel; 
Gyroscope gyro; 
Compass compass; 

int time = 0; 
float gx, gy, gz, ax, ay, az, mx, my, mz; 
float yaw, pitch, roll; 
float fps = 100; 

const double compassCalibrationBias[3] = { 
524.21, 
3352.214, 
-1402.236 
}; 

const double compassCalibrationMatrix[3][3] = { 
{1.757, 0.04, -0.028}, 
{0.008, 1.767, -0.016}, 
{-0.018, 0.077, 1.782} 
}; 

void setup() 
{ 
Serial.begin(115200); 
Serial.println("Begin init..."); 
accel.begin(); 
gyro.begin(); 
compass.begin(); 
compass.calibrateMatrix(compassCalibrationMatrix, compassCalibrationBias); 
Serial.println("Initialization completed"); 
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
delay(1); 
time ++; 
unsigned long startMillis = millis(); 
accel.readGXYZ(&ax, &ay, &az); 
gyro.readRadPerSecXYZ(&gx, &gy, &gz); 
compass.readCalibrateGaussXYZ(&mx, &my, &mz); 
filter.setKoeff(fps, BETA); 
filter.update(gx, gy, gz, ax, ay, az, mx, my, mz); 
yaw = filter.getYawDeg(); 
pitch = filter.getPitchDeg(); 
roll = filter.getRollDeg(); 

Serial.print("yaw: "); 
Serial.print(yaw); 
Serial.print("\t\t"); 
Serial.print("pitch: "); 
Serial.print(pitch); 
Serial.print("\t\t"); 
Serial.print("roll: "); 
Serial.println(roll); 
//if(yaw >= 90)RVO(); 
unsigned long deltaMillis = millis() - startMillis; 
fps = 1000 / deltaMillis; 
//RVO();
//RVC();
Serial.print(digitalRead(2));
Serial.print(digitalRead(3));
RVO();
delay()
} 

void RVO() 
{ 
  
if (digitalRead(2) == 1 && digitalRead(3) == 0) S1.write(90);
if (digitalRead(2) == 0 && digitalRead(3) == 1) S1.write(0);
} 

void RVC() 
{ 
if (digitalRead(2) == 1 && digitalRead(3) == 0) S1.write(180);
if (digitalRead(2) == 0 && digitalRead(3) == 1) S1.write(90);
} 

void LVO() 
{ 
if (digitalRead(4) == 1 && digitalRead(5) == 0) S2.write(0);
if (digitalRead(4) == 0 && digitalRead(5) == 1) S2.write(90);
} 

void LVC() 
{ 
if (digitalRead(4) == 1 && digitalRead(5) == 0) S2.write(90);
if (digitalRead(4) == 0 && digitalRead(5) == 1) S2.write(180);
} 
