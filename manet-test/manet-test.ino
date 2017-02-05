  volatile byte state=LOW;

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(0,magnet_rise,FALLING);
  pinMode(13,OUTPUT);
  pinMode(11,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13,LOW);
  delay(100);
}

void magnet_rise() {
  digitalWrite(13,HIGH);
}

void magnet_fall() {
  digitalWrite(13,LOW);
}

