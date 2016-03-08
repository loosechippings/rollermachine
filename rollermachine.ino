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
   rpm = 1000/(millis() - timeold)*revolutions;
   timeold = millis();
   revolutions = 0;
   
   myservo.write(180-((rpm/10.0)*180));
   delay(200);
 }
 
 void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   revolutions++;
 }
