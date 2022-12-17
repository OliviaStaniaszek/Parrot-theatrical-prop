#include <Servo.h>
//#include <PWMServo.h>
Servo Lservo;  // create servo object to control a servo
Servo Rservo;

int maxDegree = 80;
int minDegree = 10;

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int speed;
int ledPin=7;

void setup() {
  Lservo.attach(5);  // attaches the servo on pin 9 to the servo object
  Rservo.attach(6);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int nspeed = getSpeed();
  Serial.println(nspeed);
  if(nspeed <=20){
    //wings open
    Lservo.write(minDegree);
    Rservo.write(180-minDegree);
  }else if(nspeed >= 40){
    //wings closed
    Lservo.write(maxDegree);
    Rservo.write(180-maxDegree);
  }else{
		//flap wings
    openWing();
    closeWing();
  }
}

//gets current value from potentiometer and maps it to a suitable speed value
int getSpeed(){
	sensorValue = analogRead(sensorPin);
	speed = map(sensorValue, 0, 1028, 15, 50);
	return speed;
}

//moves the servos from the minimum degree to the maximum degree
void openWing(){
  int lDegree;
  int rDegree;
  for (int i = minDegree; i<=maxDegree; i++){
    lDegree = i;
    rDegree = 180 - lDegree;
    Lservo.write(lDegree); // sets the servo position according to the scaled value
    Rservo.write(rDegree);

		//led bink
    if(i%20==0){ //led turns off every multiple of 20
	    digitalWrite(ledPin, LOW);  
    }
    else if(i%10==0){ //if not a multiple of 20, but a multiple of 10, led turns on
      digitalWrite(ledPin, HIGH);
    }
    int nspeed = getSpeed();
    delay(nspeed);   
  } 
}

//moves servos from max degree to minimum degree
void closeWing(){
  int lDegree;
  int rDegree;
  for (int i=maxDegree; i>=minDegree; i--){
    lDegree = i;
    rDegree = 180 - lDegree;
    Lservo.write(lDegree);
    Rservo.write(rDegree);
    if(i%20==0){
	    digitalWrite(ledPin, LOW);  
    }
    else if(i%10==0){
      digitalWrite(ledPin, HIGH);
    }
    int nspeed = getSpeed();
    delay(nspeed);   
  }  
}