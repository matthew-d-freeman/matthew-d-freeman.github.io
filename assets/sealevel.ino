#include "Grove_Temperature_And_Humidity_Sensor.h"                //Temperature and Humidity library
#include "Ultrasonic.h"                                           //Ultrasonic Ranger library
#include <SD.h>                                                   //SD library

#define DHTTYPE DHT22                                             //temperature and humidity model
#define DHTPIN 2                                                  //temperature and humidity pin

const int chipSelect = 4;                                         //SD pin
int led[] = {6, 7};                                               //LED Order: Blue, Green
int anne = A0; int light = A1;                                    //Annemometer pin and Light Sensor pin    
int readingMinutes = 1; int readingTime;                          //changing reading time from minute to milliseconds
int readTime = readingMinutes * 60000;                            //Converting read time from minutes to milliseconds
int debug = 50;                                                   //Debug delay time                                                                  
int lightReading; int lightPercent;                               //Light sensor variables
int windCount; int windSpeed;                                     //Annemometer variables

File myFile;                                                      //Creating file state for SD                        

Ultrasonic ultrasonic(5);                                         //Range finder pin
long RangeInCenti;                                                //Range in centimeters for ultasonic ranger

DHT dht(DHTPIN,DHTTYPE);                                          //DHT Setup                                                   
float tempval;                                                    //Decimal for temperature   
float humidity;                                                   //Decimal for humidity value              

void blink(int blinkNumber, int ledNumber) {                      //Function for blinking LEDs for diagnostic purposes     
  digitalWrite(led[0],LOW);       
  for(int i=0; i < blinkNumber; i++) {                            //count up from zero to number of blink times           
    digitalWrite(led[0], LOW);                                    //Turns of diagnostic LED                           
    digitalWrite(led[ledNumber], HIGH); delay(1000);              //Turns LED on set amount of times                          
    digitalWrite(led[ledNumber],LOW); delay(1000);                //Turns LED off set amount of times                          
  }                                                                      
}                                                                     

void setup() {
  Serial.begin(9600);                                             //Initialize Serial
    while(!Serial);                                               //Hold until Serial begins

  for (int p = 0; p < 3; p++) {                                   //Initialize LED pins
    pinMode(led[p], OUTPUT);                                      //Sets LED pins as outputs
  } delay(debug);                                                 //Debounce delay              

  pinMode(anne,OUTPUT); delay(debug);                             //Annemometer initialization
  dht.begin(); delay(debug);                                      //Initialize Temp and Humidity sensor
  pinMode(light,INPUT); delay(debug);                             //Initialize Light Sensor

  Serial.print("Initializing SD card...");                        //Print to serial that SD is starting
  digitalWrite(led[0],HIGH);                                      //Blue LED means that setup is beginning for device
    delay(debug);                                                 //Debounce delay
  if (!SD.begin(chipSelect)) {                                    //Starting SD
    Serial.println("initialization failed.");                     //Print to serial that SD failed
    blink(2,0);                                                   //2 Blue blinks for SD card startup failure
    while(!SD.begin(chipSelect));
  }                                                                         
  Serial.println("initialization done."); delay(debug);           //Print to serial that SD starup is done

  myFile = SD.open("sealevel.csv", FILE_WRITE); delay(debug);     //creates file named sea_level.csv meaning its a commas deleted excel
 
  if (myFile) {                                                             
    Serial.println("Initializing Headers");                       //Print to serial that headers are being made
      myFile.print("time_min,"); myFile.print("temp,"); myFile.print("humidity_percent,"); 
      myFile.print("wind_count,"); myFile.print("wind_speed_mph,"); myFile.print("light_raw,"); myFile.print("light_percent,"); 
      myFile.println("tide_distance_cm,"); myFile.close();
  delay(debug);                                                   //Debounce delay
    Serial.println("Headers written.");                           //print to serial if the file was composed correctly
  } else {                                                              
    Serial.println("Failed to open file for writing headers.");   //Serial print if file is writing properly
      blink(4,0);                                                 //4 Blue blinks for file creation errors
      while(!myFile);
  }                                                                   
  delay(debug);                                                   //Debounce delay
    Serial.println("Setup is complete");                          //Print to serial that everything is completed
      digitalWrite(led[0],LOW);                                   //Turn off Blue LED to show setup has stopped
      digitalWrite(led[1],HIGH);                                  //Turn on Green LED to show everthing is ready
      delay(5000);                                                //Delay 5 seconds
      digitalWrite(led[1],LOW);                                   //Turn off Green LED to save power
  delay(debug);                                                   //Debounce delay
}                                                                     

void loop() {                                                       

  delay(readTime);

  readingTime += readingMinutes;                                  //Increases the reading time by however long the reading minutes was set to

  lightReading = analogAverage(10, light);                        //function to read light average
  lightPercent = map(lightReading, 0, 800, 0, 100);               //Maps light level to a percentage based system

  windCount = analogAverage(10, anne);                            //Averages the count of 10 windspeed readings
  windSpeed = windCount/2.2993;                                   //Calibration to convert counts from annemometer to windspeed in MPH

  RangeInCenti = ultrasonic.MeasureInCentimeters();               //Reads ultrasonic sensors and gives a distance

  tempval = averageDHT(10, dht.readTemperature());                //Function to read average temp
  humidity = averageDHT(10, dht.readHumidity());                  //Function to read average humidity

  check();                                                        //checks to make sure sensors are working properly

  myFile = SD.open("sealevel.csv", FILE_WRITE);                   //creates file named sea_level.csv meaning its a commas deleted excel

  if (myFile) {                                                   //Adds to myFile if open
    myFile.print(readingTime); myFile.print(","); myFile.print(tempval); myFile.print(","); myFile.print(humidity); myFile.print(",");
    myFile.print(windCount); myFile.print(","); myFile.print(windSpeed); myFile.print(","); myFile.print(lightReading); myFile.print(","); 
    myFile.print(lightPercent); myFile.print(","); myFile.println(RangeInCenti); myFile.close();
    Serial.println("Data Recorded");
  }
  blink(1,1);                                                     //Blinks green once to show data has been taken
}                                                                                                                                                                  

float averageDHT(int numReadings, int sensor) {                   //Average Temp and Humidity Readings
  float total = 0.0;                                              //Reset total to 0.0
  for(int i=0; i<numReadings; i++){                               //Count up from 0 to 1 below read count                           
    total += sensor;                                              //Read Sensor
    delay(debug);                                                 //Delay between readings
  } delay(debug);                                                 //Debounce delay
  return total/numReadings;                                       //Return Avereged Humidity Readings
}                        

int analogAverage(int numReadings, int sensor) {                  //Average Analog Readings
  int total = 0;                                                  //Reset total to 0
  for(int i=0; i<numReadings; i++)  {                             //Count up from 0 to 1 below read count   
    total += analogRead(sensor);                                  //Read Light Sensor
    delay(debug);                                                 //Delay between readings
  } delay(debug);                                                 //Debounce delay
  return total/numReadings;                                       //Return Averaged Light Readings
}

void check() {                                                    //Checks to see if the Light sensor is reading properly
  if (lightReading < 0 || lightReading > 1023)  {                 //Check light sensor value
    lightReading = -1; lightPercent = -1;                         //Change light values to -1 to show error
  } delay(debug);                                                 //Debounce delay
  if (windCount < 0 || windCount > 1023)  {                       //Check wind sensor value
    windCount = -2; windSpeed = -2;                               //Change wind values to -1 to show error
  } delay(debug);                                                 //Debounce delay
  if (RangeInCenti < 0 || RangeInCenti > 400) {                   //Check distance value
    RangeInCenti = -3;                                            //Change distance value to -1 to show error
  } delay(debug);                                                 //Debounce delay
  if (humidity < 0 || humidity > 100)  {                          //Check humidity value
    humidity = -4.0;                                              //Change humidity value to -1 to show error
  } delay(debug);                                                 //Debounce delay
  if (tempval < -40 || tempval > 80)  {                           //Check temperature value
    tempval = -5.0;                                               //Change temperature value to -1 to show error
  } delay(debug);                                                 //Debounce delay
  return;                                                         //Returns from check
}
