#include <Servo.h>

Servo servo_1; 

int trig = 4; 
int echo = 5; 
int servo_pin = 3; 

int pos = 0;    // servo starting position
float duration,distance;

void setup()  {
  Serial.begin(115200);
  Serial.println("Radar Start");
  servo_1.attach(servo_pin); // start servo control
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}


void loop() {
for (pos = 0; pos <= 360; pos += 1) { // goes from 0 degrees to 360 degrees
    // in steps of 1 degree
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(45); // delay to allow the servo to reach the desired position
    dist_calc(pos);
  }
 
  for (pos = 360; pos >= 0; pos -= 1) { // goes from 360 degrees to 0 degrees
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(45);
    dist_calc(pos);
  }
}

float dist_calc(int pos){
  // trigger 40kHz pulse for ranging
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  // convert from duration for pulse to reach detector (microseconds) to range (in cm)
  duration = pulseIn(echo,HIGH); // duration for pulse to reach detector (in microseconds)
  distance = 100.0*(343.0*(duration/2.0))/1000000.0; // 100.0*(speed of sound*duration/2)/microsec conversion
 
  Serial.print("pos" , pos ); // position of servo motor
  Serial.print(" , "); // comma separate variables
  Serial.println("distance is : " , distance); // print distance in cm
}
