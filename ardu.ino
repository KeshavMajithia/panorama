#include <Servo.h>
Servo panServo;
Servo tiltServo;
int panAngle=65;
int tiltAngle = 60;
int panIncrement = 10;
bool isMoving = false;

void setup() {
  Serial.begin(9600);
  panServo.attach(9);
  panServo.write(panAngle);
  tiltServo.attach(10);
  tiltServo.write(tiltAngle);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'I') {
      initializeServo();
    } else if (command == 'Q') {
      setNewPositions();
    } else if (command == 'L' && !isMoving) {
      moveServo(120);
    } else if(command=='R' && !isMoving){
      moveServo(30);
    }else if(command=='S'){
      stopServo();
    }
  }
}
void initializeServo(){
  panServo.write(panAngle);
  tiltServo.write(tiltAngle);
}
void setNewPositions(){
  panServo.write(0);
  tiltServo.write(165);
}
void moveServo(int targetAngle){
  isMoving=true;
  int currentAngle=panServo.read();
  while(currentAngle!=targetAngle){
    if(currentAngle<targetAngle){
      currentAngle=min(currentAngle+panIncrement,targetAngle);
    }else{
      currentAngle=max(currentAngle-panIncrement,targetAngle);
    }
    panServo.write(currentAngle);
    delay(300);
    if (Serial.available()>0 && Serial.read()=='S'){
      stopServo();
      break;
    }
  }
  isMoving=false;
}
void stopServo(){
}
