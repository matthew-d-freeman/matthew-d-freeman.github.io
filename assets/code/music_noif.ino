int led[] = {2,3,4,5,6,7};  //sets an array for 
int pinCount = 6;

int loudness[] = {150,200,300,400,500,600}; //sets loudness parameters using an array

void setup() {
  for (int p = 0; p < pinCount; p++) {
    pinMode(led[p],OUTPUT);
  }
  /* Uses a for statement to create an integer known as p. This integer is then increased by one until it is one less than the pin count.
  Each value integer of p is then inputed into the pinMode function so that each pin in my led array is then initalized as an output. */
  Serial.begin(9600); //begins serial communication
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  for (int i = 0; i <= 5; i++) {
    if (sensorValue > loudness[i]) {
      digitalWrite(led[i], HIGH);
    }
  }
  for (int i = 5; i >= 0; i--) {
    if (sensorValue < loudness[i]) {
      digitalWrite(led[i],LOW);
    }
  }
  delay(20);
}