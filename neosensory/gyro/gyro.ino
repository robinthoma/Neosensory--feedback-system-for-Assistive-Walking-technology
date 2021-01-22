#include <Wire.h>
#define SDA_2 33
#define SCL_2 32

const int MPU1 = 0x69, MPU2=0x68 , MPU3 = 0x69, MPU4=0x68;

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ, gyroX, gyroY, gyroZ,rotX, rotY, rotZ;
long accelX2, accelY2, accelZ2;
float gForceX2, gForceY2, gForceZ2;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();  
  Wire.beginTransmission(MPU1);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU1);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission(); 

  Wire.beginTransmission(MPU2);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();  
  Wire.beginTransmission(MPU2);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission(); 


  Wire1.begin(SDA_2, SCL_2);
  Wire1.beginTransmission(MPU3);
  Wire1.write(0x6B);
  Wire1.write(0b00000000); 
  Wire1.endTransmission();  
  Wire1.beginTransmission(MPU3); 
  Wire1.write(0x1B);
  Wire1.write(0x00000000);
  Wire1.endTransmission(); 
  Wire1.beginTransmission(MPU3);
  Wire1.write(0x1C);
  Wire1.write(0b00000000);
  Wire1.endTransmission(); 

  Wire1.begin(SDA_2, SCL_2);
  Wire1.beginTransmission(MPU4);
  Wire1.write(0x6B);
  Wire1.write(0b00000000); 
  Wire1.endTransmission();  
  Wire1.beginTransmission(MPU4); 
  Wire1.write(0x1B);
  Wire1.write(0x00000000);
  Wire1.endTransmission(); 
  Wire1.beginTransmission(MPU4);
  Wire1.write(0x1C);
  Wire1.write(0b00000000);
  Wire1.endTransmission();

  Serial.begin(115200);
  
}

void loop(){
  GetMpuValue1(MPU1);
  Serial.print("\t ||| \t");

  GetMpuValue1(MPU2);
  Serial.println("");

 GetMpuValue2(MPU3);
  Serial.print("\t ||| \t");

  GetMpuValue2(MPU4);
  Serial.println("");

}

void GetMpuValue1(const int MPU){
  Wire.beginTransmission(MPU); 
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6);
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); 
  accelY = Wire.read()<<8|Wire.read(); 
  accelZ = Wire.read()<<8|Wire.read();
  
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6);
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read();
  gyroY = Wire.read()<<8|Wire.read();
  gyroZ = Wire.read()<<8|Wire.read(); 


  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
  Serial.print("gyro\t");
  Serial.print(rotX);
  Serial.print("\t");
  Serial.print(rotY);
  Serial.print("\t");
  Serial.print(rotZ);
  Serial.print("\tAcc\t");
  Serial.print(gForceX);
  Serial.print("\t");
  Serial.print(gForceY);
  Serial.print("\t");
  Serial.print(gForceZ);
  delay(100);
  
}

void GetMpuValue2(const int MPU){
  Wire1.beginTransmission(MPU); 
  Wire1.write(0x3B);
  Wire1.endTransmission();
  Wire1.requestFrom(MPU,6);
  while(Wire1.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); 
  accelY = Wire.read()<<8|Wire.read(); 
  accelZ = Wire.read()<<8|Wire.read();
  
  Wire1.beginTransmission(MPU);
  Wire1.write(0x43);
  Wire1.endTransmission();
  Wire1.requestFrom(MPU,6);
  while(Wire1.available() < 6);
  gyroX = Wire.read()<<8|Wire.read();
  gyroY = Wire.read()<<8|Wire.read();
  gyroZ = Wire.read()<<8|Wire.read(); 


  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
  Serial.print("gyro\t");
  Serial.print(rotX);
  Serial.print("\t");
  Serial.print(rotY);
  Serial.print("\t");
  Serial.print(rotZ);
  Serial.print("\tAcc\t");
  Serial.print(gForceX);
  Serial.print("\t");
  Serial.print(gForceY);
  Serial.print("\t");
  Serial.print(gForceZ);
  delay(100);
  
}
