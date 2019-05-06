#include <NewPing.h>

#define PING_PINT 8 
#define PING_PINE 9
#define PING_MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(PING_PINT, PING_PINE, PING_MAX_DISTANCE); // NewPing setup of pin and maximum distance.

#define MAX_DISTANCE_FROM_OBSTACLE_IN_CMS 30 // Change this if needed, depending on position of the ultrasonic sensor in the robot chasis


char t='X';
 
void setup() {
pinMode(13,OUTPUT);   //left motors forward
pinMode(12,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right motors forward
pinMode(10,OUTPUT);   //right motors reverse
//pinMode(9,OUTPUT);   //Led
Serial.begin(9600);
 
}
 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}

if(t == 'X'){
  delay(50); 
  unsigned int distanceInCms = sonar.ping() / US_ROUNDTRIP_CM; // Send ping, get ping time in microseconds (uS) and convert it to centimeters (cm)
Serial.println("Distance: " + String(distanceInCms) + "cm");

if(distanceInCms != NO_ECHO && distanceInCms < MAX_DISTANCE_FROM_OBSTACLE_IN_CMS) {
    rotate_right(90);
  } else  {
    drive_forward();
  }
}
else{
 switch(t){
  case 'F': 
    digitalWrite(10,HIGH);
    digitalWrite(13,HIGH);
    break;
  case 'B':
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    break;
  case 'L': 
    digitalWrite(13,HIGH);
    break;
  case 'R':
    digitalWrite(10,HIGH);
    break;
  default:
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);   
  }
}

}

void rotate_right(int angleInDegrees) {
  for(int i=0; i< angleInDegrees; i++) {
    turn_right();
    delay(25); // Test this out and change it approriately based on your motor speed
  }
}

void drive_forward() {
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
}

void turn_right() {
  digitalWrite(13, HIGH); 
  digitalWrite(12, LOW); 
  
  digitalWrite(10, LOW); 
  digitalWrite(11, HIGH); 
}
