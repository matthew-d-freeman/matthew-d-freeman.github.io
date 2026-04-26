int led[] = {2,3,4,5,6,7};  //sets an array for 
int pinCount = 6;

int loudness[] = {150,300,400,500,600,700}; //sets loudness parameters using an array

void turnOff() {  //I'm trying to practice for loops and arrays so this seemed like a good use
  for (int i = 0; i < pinCount; i++){
    digitalWrite(led[i],LOW);
  }
}

void setup() {
  for (int p = 0; p < pinCount; p++) {
    pinMode(led[p],OUTPUT);
  }
  /* Uses a for statement to create an integer known as p. This integer is then increased by one until it is one less than the pin count.
  Each value integer of p is then inputed into the pinMode function so that each pin in my led array is then initalized as an output. */
  Serial.begin(9600); //begins serial communication
}

void loop() {
  turnOff(); //ensures all leds are off
  int sensorValue = analogRead(A0); //initiate read of sound sensor to the the sensorValue integer
  Serial.println(sensorValue);  //print sound sensor count for troubleshooting
  if (sensorValue > loudness[0] && sensorValue < loudness[1]) {  //turn on led 1
    digitalWrite(led[0],HIGH);
  }
  else if (sensorValue > loudness[0] && sensorValue < loudness[2]) { //turn on led 2
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);
  }
  else if (sensorValue > loudness[0] && sensorValue < loudness[3]) { //turn on led 3
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);
    digitalWrite(led[2],HIGH);
  }
  else if (sensorValue > loudness[0] && sensorValue < loudness[4]) { //turn on led 4
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);
    digitalWrite(led[2],HIGH);
    digitalWrite(led[3],HIGH);
  }
  else if (sensorValue > loudness[0] && sensorValue < loudness[5]) { //turn on led 5
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);
    digitalWrite(led[2],HIGH);
    digitalWrite(led[3],HIGH);
    digitalWrite(led[4],HIGH);
  }
  else if (sensorValue > loudness[0]) { //turn all on
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);
    digitalWrite(led[2],HIGH);
    digitalWrite(led[3],HIGH);
    digitalWrite(led[4],HIGH);   
    digitalWrite(led[5],HIGH);
  }
  else {
    turnOff();
  }
  delay(30);
}
