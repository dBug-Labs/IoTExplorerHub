#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

int buzzer = 8;

//ultrasonic sensor 1
int echoPin1 = 11; 
int initPin1 = 12;
int distance1 =0;

//ultrasonic sensor 2
int echoPin2 = 7;
int initPin2 = 6;
int distance2 =0;

int isDisSensor = 0;
int isDisSensor2 = 0;

#define sensorPower 7
#define sensorPin A0

void setup() {

   myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  	pinMode(sensorPower, OUTPUT);
	// Initially keep the sensor OFF
	digitalWrite(sensorPower, LOW);

  pinMode(initPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(initPin2, OUTPUT);
  pinMode(echoPin2, INPUT);


    pinMode(13,OUTPUT);
  pinMode(3,INPUT);

  Serial.begin(9600);
 }

void loop() {

  distance1 = getDistance(initPin1, echoPin1);
  printDistance(1, distance1);
  delay(1000);
 if (distance1<=3){
    tone(buzzer, 500);
delay(500);
noTone(buzzer);
delay(500);
  }
 
  
  distance2 = getDistance(initPin2, echoPin2);
  printDistance(2, distance2);
  delay(1000);
  if (distance2<=3){
    tone(buzzer, 500);
delay(500);
noTone(buzzer);
delay(500);
  }


   if (digitalRead(3)== LOW)
  {
    Serial.println("object detected");
    
  	Serial.print("moisure value: ");
	Serial.println(readSensor());
    	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// Allow power to settle

	int val = analogRead(sensorPin);	// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
  if(val<=800){
    Serial.println("wet waste");
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);     // waits 15 ms for the servo to reach the position
  }}
  else if (val>800)
  {
    Serial.println("dry waste");
    for (pos = 180; pos >= 90; pos -= 1) { // goes from 90 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); 
     // waits 15 ms for the servo to reach the position
  }
  }
  }
  
  



}



int getDistance (int initPin, int echoPin){
 digitalWrite(initPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(initPin, LOW); 
 
 unsigned long pulseTime = pulseIn(echoPin, HIGH); 
 int distance = pulseTime/58;
 return distance;
 
}
    //  This function returns the analog soil moisture measurement
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// Allow power to settle
	int val = analogRead(sensorPin);	// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// Return analog moisture value
}

//display space left in respective bins
void printDistance(int id, int dist) {
    Serial.print("bin number ");
    Serial.print(id);
    Serial.print(":  ");
  
      
      Serial.print(dist, DEC);
      Serial.println(" cm");
    }



