int x,y;
void setup() {
 pinMode(A0, INPUT); 
 pinMode(A1, INPUT); 
 pinMode(D6, OUTPUT); 
 pinMode(D8,OUTPUT); 
 Serial.begin(115200);
}

void loop() {
  x=analogRead(A0);
  y=analogRead(A1);
  Serial.print("FSR1=");
  Serial.print(x);
  Serial.print("FSR2=");
  Serial.println(y);
// if(x>100){
 // digitalWrite(D6,HIGH);
 // delay(20);
 // digitalWrite(D6,LOW);
// }
 //if (y>100){
 // digitalWrite(D8,HIGH);
  //delay(20);
  // digitalWrite(D8,LOW);
// }

}
