int led1 = 2;
int button1 = 8;
unsigned long start;
unsigned long end;
unsigned long reaction;
int timer = 2000;
int reset = 3000;

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(button1,INPUT);
  digitalWrite(button1,HIGH);
  Serial.begin(9600);
}

void loop() {

  digitalWrite(led1,HIGH);
    delay(timer);
  digitalWrite(led1,LOW);
   start = millis();
  while (digitalRead(button1) == HIGH){
  }
  end = millis();
  reaction = end - start;
  Serial.println(reaction);
  delay(2000);
}
