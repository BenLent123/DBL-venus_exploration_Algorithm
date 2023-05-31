#include <Servo.h>  
const int pingPin = 9;
Servo servoLeft;                             
Servo servoRight;
Servo ultrasound;
Servo gripper;
int counter = 0;
int scanRes = 0;
int leftSensor = 3; // TO BE CHANGED
int rightSensor = 3; // TO BE CHANGED

void setup() {

Serial.begin(9600);
servoLeft.attach(13);                   
servoRight.attach(12);
gripper.attach(10);
ultrasound.attach(11); 
sensorsetup();

}


void sensorsetup(){
  ultrasound.write(90);
  delay(100);
  return(1);
}


void loop() {
  long USDistance;
  counter++;

    if (counter > 10){
    scanRes = periodicScan();
    counter = 0;
    ultrasound.write(90);
    if (scanRes = 0) {
      backward();
      delay(200);
      spinL();
      delay(300);
    }
    if (scanRes = 180){
      backward();
      delay(200);
      spinR();
      delay(300);
    }
   
  }
  
  ultrasound.write(50); 
  for(int i = 50;i<130;i++){
    ultrasound.write(i);
    USDistance = ping();
    if (USDistance > 20 || USDistance == 0){
    forward();
   
  }
  else {
    backward();
    delay(200);
    spinR();
    delay(250);
    ultrasound.write(90);
  }

    
  } 

}



long ping(){
  long duration, USDistance;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  USDistance = duration / 29 / 2;
  printDistance(USDistance);
  return(USDistance);
}

void printDistance(long USDistance){
  Serial.print(USDistance);
  Serial.print("cm");
  Serial.println();
}

void forward() {
  servoLeft.attach(13);                   
  servoRight.attach(12);
  servoLeft.writeMicroseconds(1300);         
  servoRight.writeMicroseconds(1700);
}    

void backward() {
  servoLeft.attach(13);                   
  servoRight.attach(12);
  servoLeft.writeMicroseconds(1700);         
  servoRight.writeMicroseconds(1300);
}   

void spinR() {
  servoLeft.attach(13);                   
  servoRight.attach(12);
  servoLeft.writeMicroseconds(1700);         
  servoRight.writeMicroseconds(1700);
} 

void spinL() {
  servoLeft.attach(13);                   
  servoRight.attach(12);
  servoLeft.writeMicroseconds(1300);         
  servoRight.writeMicroseconds(1300);
}  

void stop() {
  servoLeft.detach();
  servoRight.detach();
}  


int periodicScan() {
long USDistance;
int n = -1;
stop();
for (int i = 0; i<200; i = i + 180){
ultrasound.write(i);
delay(1000);
USDistance = ping();

if (USDistance < 20 && USDistance != 0){
    n = i;
    return(n);
  }

}
return(n);
}


void open_gripper() {
gripper.write(90);// set the servo position to 90 degrees 
delay(1000);// wait for 1 sec
}

void close_gripper(){
gripper.write(180);
delay(1000);
}



void infra_ping() 
{
  // check the outputs of the pins 
  int infra_ls = digitalRead(leftSensor);
  int infra_rs = digitalRead(rightSensor);

}

/*void infra_action(){
   //00 = both on white -> move forward
  if (infra_ls == 0 && infra_rs == 0)
  {
    forward();
    //GRIPPER KIT?
  }

  else if (infra_ls == 1 && infra_rs == 1)
  {
    backward();
  }
  

  //01 = right sensor on black -> turn left
  else if (infra_ls == 0 && infra_rs == 1)
  {
    backward();
    delay(150);
    spinL();
  }

  //10 = left sensor on black -> turn right
  else if (infra_ls == 1 && infra_rs == 0)
  {
    backward();
    delay(150);
    spinR();
  }
}
*/



