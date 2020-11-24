#include<Servo.h>
#include "IRremote.h"
//Stepper Motor Variable Declaration
const int in1 = 9;
const int in2 = 10;
const int in3 = 11;
const int in4 = 12;
int step_num = 0;
int RECEIVER2 = 13;
int button = 0;

//IR Receiver and Remote Initialization
IRrecv irrecv(RECEIVER2);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

//Ultrasonic Sensor Variable Declaration
const int trigPin = 6;
const int echoPin = 8;
long duration;
double distance;

//Servo Motor Variable Declaration
Servo servo;
int Rot = 0;

//Other Variables:
//Remote State
int Click;
//Servo Angle
int Ang = 0;



void setup() {
  // put your setup code here, to run once:
  //Stepper Motor Pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //Ultrasonic Sensor Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, btn, FALLING);
  
  servo.attach(5);
  servo.write(90);

  Serial.begin(9600);
}

void loop() {

  if (button == 1){
    delay(1000);

    forward(1950); 
    delay(50);
    right();
    delay(50);
    forward(1950);
    delay(250);
    left();
    delay(50);
    forward(1950);
    
    button = 0;
  }
  
  Dist();
  //forward
  //right
  //forward
  //left 
  //forward
}

void forward(int steps){
   int k = 0;
    while (k < steps) {
      OneStep(false);
      delay(2);
      k = k + 1;
    }
}

void left(){
  servo.write(35);
  forward(1600);
  servo.write(90);
}

void right(){
  servo.write(145);
  forward(1670);
  servo.write(90);
}

void ServoMove(int Click) {
  //If button from remote is clicked, 0,1 position -- Select Type of Steering Movement
  if (Click == 0) {
    Ang = Ang + 1;
    servo.write(Ang);
    delay(10);
  }
  else if (Click == 1) {
    Ang = Ang - 1;
    servo.write(Ang);
    delay(10);
  }
  Dist();
}

void btn() {
  button = 1;
}

void Dist() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  if (distance == 1196) {
    distance = 0;
  }
}

//Stepper Motor Control Per step
void OneStep(bool dir) {
  if (dir) {
    switch (step_num) {
      case 0:
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        break;
      case 1:
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        break;
      case 2:
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        break;
      case 3:
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        break;
    }
  }
  else {
    switch (step_num) {
      case 0:
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        break;
      case 1:
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        break;
      case 2:
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        break;
      case 3:
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        break;
    }
  }
  step_num++;
  if (step_num > 3) {
    step_num = 0;
  }
}
