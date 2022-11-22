#include <Servo.h>          // Servo motor library
#include <NewPing.h>        // Ultrasonic sensor function library

// L298N control pins
const int LeftMotorForward = 11;
const int LeftMotorBackward = 10;
const int RightMotorForward = 9;
const int RightMotorBackward = 8;

// HC-SR04 sensor pins
// analog I/P
#define trig_pin A5 
#define echo_pin A4 

// Maximum distance we want to ping for
#define maximum_cm 250

// initializing
boolean moveForward = false;
int cm_away = 100;

// sensor function
NewPing sonar(trig_pin, echo_pin, maximum_cm); 

// servo motor function
Servo servo_motor;

void setup(){

    pinMode(RightMotorForward, OUTPUT);
    pinMode(LeftMotorForward, OUTPUT);
    pinMode(LeftMotorBackward, OUTPUT);
    pinMode(RightMotorBackward, OUTPUT);

    // servo pin
    servo_motor.attach(2); 

    servo_motor.write(90);
    delay(2000);
    cm_away = readPing();
    delay(100);
    cm_away = readPing();
    delay(100);
    cm_away = readPing();
    delay(100);
    cm_away = readPing();
    delay(100);
    Serial.begin(9600);
}


void loop(){

    int distanceRight = 0;
    int distanceLeft = 0;
    delay(50);

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 

    if (cm_away <= 20){
        moveStop();
        delay(300);
        backward();
        delay(400);
        moveStop();
        delay(300);
        distanceRight = lookRight();
        delay(300);
        distanceLeft = lookLeft();
        delay(300);

        // determine where to move next
        if (cm_away >= distanceLeft) {
            turnRight();
            moveStop();
        } else {
            turnLeft();
            moveStop();
        }

    } else {
        forward(); 
    }

    distance = readPing();
}

////////////////////////////////////////////////////

// helper functions

void moveStop(){

    digitalWrite(RightMotorForward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorBackward, LOW);

}

void forward(){
    
    if(!moveForward){

        moveForward=true;
        
        digitalWrite(LeftMotorForward, HIGH);
        digitalWrite(RightMotorForward, HIGH);
    
        digitalWrite(LeftMotorBackward, LOW);
        digitalWrite(RightMotorBackward, LOW); 
    }
}

void backward(){
    moveForward=false;

    digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(RightMotorBackward, HIGH);

    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorForward, LOW); 
}

void turnRight(){
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorBackward, HIGH);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorForward, LOW);

    delay(500);

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
}

void turnLeft(){
    digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(RightMotorForward, HIGH);

    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);

    delay(500);

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
}

int lookRight(){  
    servo_motor.write(10);
    delay(500);
    int distance = readPing();
    delay(100);
    servo_motor.write(90);
    return distance;
    delay(100);
}

int lookLeft(){
    servo_motor.write(170);
    delay(500);
    int distance = readPing();
    delay(100);
    servo_motor.write(90);
    return distance;
    delay(100);
}

int readPing(){
    delay(70);
    int cm = sonar.ping_cm();
    if (cm == 0) {
        cm = 250;
    }
    return cm;
}