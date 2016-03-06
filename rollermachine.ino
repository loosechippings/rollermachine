#include <Servo.h>

/*
Arduino Hall Effect Sensor Project
by Arvind Sanjeev
Please check out  http://diyhacking.com for the tutorial of this project.
DIY Hacking
*/

 Servo myservo;
 volatile byte revolutions;
 unsigned int rpm;
 unsigned long timeold;
 int pos=0;
 
 void setup()
 {
   Serial.begin(9600);
   attachInterrupt(0, magnet_detect, FALLING);//Initialize the intterrupt pin (Arduino digital pin 2)
   revolutions = 1;
   rpm = 0;
   timeold = 0;
   pinMode(13, OUTPUT);  
   myservo.attach(9);
 }
 void loop()//Measure RPM
 {
   Serial.print(revolutions);
   Serial.print(" - ");
   Serial.print(millis()-timeold);

   rpm = 1000/(millis() - timeold)*revolutions;
   timeold = millis();
   revolutions = 0;
   
   Serial.print(" - ");
   Serial.print(rpm);
   Serial.print(" - ");
   Serial.println(rpm/10.0);
   
   myservo.write((rpm/10.0)*180);
   delay(500);
 }
 
 void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   revolutions++;
   Serial.println("detect");
   digitalWrite(13,HIGH);
   delay(1000);
   digitalWrite(13,LOW);
 }
