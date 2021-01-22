#include"LIS3DHTR.h" //include accelerometer library
LIS3DHTR<TwoWire> lis; //Initialize accelerometer
int FSR1,FSR2;
void setup() {
  Serial.begin(115200); //Start serial communication
  lis.begin(Wire1); //Start accelerometer 
   pinMode(A0, INPUT); 
   pinMode(A1, INPUT);

  //Check whether accelerometer is working 
  if (!lis) { 
    Serial.println("ERROR"); 
    while(1);
  }
  lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); //Data output rate (5Hz up to 5kHz)
  lis.setFullScaleRange(LIS3DHTR_RANGE_2G); //Scale range (2g up to 16g)
}
 
void loop() {
  FSR1=analogRead(A0);
  FSR2=analogRead(A1);
  
  
  float x_values, y_values, z_values; //Initialize variables to store accelerometer values
  x_values = lis.getAccelerationX(); //store x-axis accelerometer values 
  y_values = lis.getAccelerationY(); //store y-axis accelerometer values
  z_values = lis.getAccelerationZ(); //store z-axis accelerometer values
  Serial.print(FSR1);
  Serial.print(",");
  Serial.print(FSR2);
  Serial.print(",");
  Serial.print(x_values);Serial.print(","); //print x-axis accelerometer values
  Serial.print(y_values);Serial.print(",");//print y-axis accelerometer values
  Serial.print(z_values);//print z-axis accelerometer values
  Serial.println(); //print a new line 
 
  delay(50); //delay between each accelerometer readings 
}
