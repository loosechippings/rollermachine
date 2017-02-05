#include <Servo.h>

/*
Arduino Hall Effect Sensor Project
by Arvind Sanjeev
Please check out  http://diyhacking.com for the tutorial of this project.
DIY Hacking
*/

 Servo myservo;
 volatile byte revolutions;
 int distance;
 float rpm;
 unsigned long timeold;
 int pos=0;
 boolean racing=false;

 // 15 because 4 magnets on the roller, 7.5 ratio between roller and wheel circ
 float rpmcalc=15/7.5;
 // 7.2 is ratio of roller circ to wheel circ, 2 is number of magenets on roller, 2.1 is circ of wheel in meters
 float revolutionsToMeters=0.14/2/2.1
 
 void setup()
 {
   attachInterrupt(0, magnet_detect, FALLING);//Initialize the intterrupt pin (Arduino digital pin 2)
   revolutions = 0;
   distance=0;
   rpm = 0;
   timeold = 0;
   pinMode(13, OUTPUT);  
   myservo.attach(9);
   myservo.write(180);
   Serial.begin(9600);
 }
 
 void loop()//Measure RPM and distance
 {
     noInterrupts();
     rpm = 1000/(millis() - timeold)*revolutions*rpmcalc;
     distance=revolutions;
     revolutions = 0;
     interrupts();

     Serial.print(distance*revolutionsToMeters);
     Serial.print(",");
     Serial.println(millis()-timeold);

     timeold = millis();
  
     // use this to display rpm
     // 222 revolutions of the wheel per minute is ~30kph
     // myservo.write(180-((rpm/222.0)*180));
  
     // use this to display distance
     //myservo.write(180-((distance/227.0)*180));
  
     //if (distance>=227) {
     // digitalWrite(12,HIGH);
     // racing=false;
     //}


   delay(50);
 }


 
 void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   revolutions++;
 }
