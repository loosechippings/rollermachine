#include <Servo.h>

/*
Arduino Hall Effect Sensor Project
by Arvind Sanjeev
Please check out  http://diyhacking.com for the tutorial of this project.
DIY Hacking
*/

 Servo myservo;
 volatile byte revolutions;
 float rpm;
 unsigned long timeold;
 int pos=0;

 // 15 because 4 magnets on the roller, 7.5 ratio between roller and wheel circ
 float rpmcalc=15/7.5;
 
 void setup()
 {
   attachInterrupt(0, magnet_detect, FALLING);//Initialize the intterrupt pin (Arduino digital pin 2)
   revolutions = 1;
   rpm = 0;
   timeold = 0;
   pinMode(13, OUTPUT);  
   myservo.attach(9);
 }
 
 void loop()//Measure RPM
 {
   noInterrupts();
   rpm = 1000/(millis() - timeold)*revolutions*rpmcalc;
   revolutions = 0;
   interrupts();
   
   timeold = millis();

   // 222 revolutions of the wheel per minute is ~30kph
   myservo.write(180-((rpm/222.0)*180));

   delay(200);
 }
 
 void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   revolutions++;
 }
