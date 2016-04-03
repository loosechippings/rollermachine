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
 
 void setup()
 {
   attachInterrupt(0, magnet_detect, FALLING);//Initialize the intterrupt pin (Arduino digital pin 2)
   attachInterrupt(1, button_detect, RISING);
   revolutions = 0;
   distance=0;
   rpm = 0;
   timeold = 0;
   pinMode(12, OUTPUT);  
   myservo.attach(9);
   myservo.write(180);
 }
 
 void loop()//Measure RPM and distance
 {
   if (racing) { 
     noInterrupts();
     rpm = 1000/(millis() - timeold)*revolutions*rpmcalc;
     distance+=revolutions;
     revolutions = 0;
     interrupts();
     
     timeold = millis();
  
     // use this to display rpm
     // 222 revolutions of the wheel per minute is ~30kph
     // myservo.write(180-((rpm/222.0)*180));
  
     // use this to display distance
     myservo.write(180-((distance/227.0)*180));
  
     if (distance>=227) {
      digitalWrite(12,HIGH);
      racing=false;
     }
   }

   delay(50);
 }

 void button_detect()
 {
  racing=true;
  distance=0;
  digitalWrite(12,LOW);
 }
 
 void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   revolutions++;
 }
