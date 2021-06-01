#include <Servo.h>
#define echoPin 3 
#define trigPin 2 
#define buttonPin 5 

Servo servo;
long duration; 
int distance; 
int angle=10;
int pirPin = 4;                 
int pirStat = 0;
int currentState = HIGH;
int prevState = HIGH;
int app = 0;
int distance_vector[6];
int minPosition = 0;

void setup() {
  setColorRGB(0,0,0);
  pinMode(pirPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  servo.attach(9);
  servo.write(angle);
}

void distanceFind(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
}

void servoMove(){
  int i = 0;
  for(angle = 0; angle <= 180; angle+=30)  
  {                                  
    servo.write(angle); 
    distanceFind();
    distance_vector[i] = distance;   
    delay(150);  
    i++;                 
  } 
}
void findMinPosition(){
  minPosition = 0;
  for(int i = 0; i < 7; i++){
    if(distance_vector[minPosition] > distance_vector[i]){
       minPosition = i;
    }
  }
}
void loop() {
  currentState = digitalRead(buttonPin);
  if(currentState != prevState){
    if(currentState == LOW){
      app++;
    }
  }
  if(app == 2 && digitalRead(pirPin) == HIGH){
    servoMove();
    findMinPosition();
    setColorRGB(255,0,0);
    Serial.println(minPosition*30);
    servo.write(minPosition*30);
    delay(150);
  }
  if(app == 1){
    setColorRGB(255,0,0);
    servoMove();
    findMinPosition();
    Serial.println(minPosition*30);
    servo.write(minPosition*30);
    app++;
  }
}

void setColorRGB(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(11, red);
  analogWrite(10, green);
  analogWrite(8, blue);
}
