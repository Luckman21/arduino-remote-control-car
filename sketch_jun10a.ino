#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10,9); // RX, TX
int led = 2;
int power = LOW; //Engine light
int Signal; //the data recieved (used to send data to subroutine)
int Data; //the data recieved (saves data sent to subroutine)

//Directions
const int leftForward = 4;
const int leftBackward = 3;
const int rightForward = 5;
const int rightBackward = 6;

void setup(){
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Bluetooth.println("Engine started!/n/nControls:/n/t'Up arrow' or 'W' (Forward)/n/t'Down arrow' or 'S' (down)/n/t'Left arrow' or 'A' (left)/n/t'Right arrow' or 'D' (right)/n/t'X' or '3' (Stop)n/t'SELECT' or '_' (Engine light on)");
  Serial.println("Connected to controller!");

  //Motor and LED pin set up
  pinMode (led, OUTPUT);
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);
}

void loop(){
  if (Bluetooth.available()){ // wait for data recieved
    Signal=Bluetooth.read();
    digitalWrite(led, power);

    blue(Signal);
  }
}

void blue(int data){
  
  //If forward is pressed, both motors drive forward
  if(data == 'W'){
    digitalWrite(leftForward , HIGH);
    digitalWrite(rightForward , HIGH);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightBackward , LOW);
  }
  
  //If reverse is pressed, both motors drive reverse
  else if(data == 'S'){
    digitalWrite(leftForward , LOW);
    digitalWrite(rightForward , LOW);
    digitalWrite(leftBackward , HIGH);
    digitalWrite(rightBackward , HIGH);
  }

  //If right is pressed, left motor drives forward while the right motor drives reverse
  //This is done to cause the car to pivot, because the front tires have too much friction
  //To turn the car as it is in motion
  else if(data == 'D'){
    digitalWrite(leftForward , HIGH);
    digitalWrite(rightForward , LOW);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightBackward , HIGH);
  }
  
  //If left is pressed, left motor drives reverse while the right motor drives forward
  //This is done to cause the car to pivot, because the front tires have too much friction
  //To turn the car as it is in motion
  else if(data == 'A'){
    digitalWrite(leftForward , LOW);
    digitalWrite(rightForward , HIGH);
    digitalWrite(leftBackward , HIGH);
    digitalWrite(rightBackward , LOW);
  }

  //If SELECT is pressed the engine LED is switched on/off
  else if(data == '_'){

    if(power == HIGH){
      power = LOW;
    }
    else{
      power = HIGH;
    }
  }

  //If stop is pressed all motors will halt and engine light will turn off
  else if(data == '3'){
    digitalWrite(leftForward , LOW);
    digitalWrite(rightForward , LOW);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightBackward , LOW);
    power = LOW;
  }
  //If any other buttons are pressed, the car will not change its behaviour
  else{;}
}
