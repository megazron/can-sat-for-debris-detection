#include "DHT.h"
#include <Wire.h>

#include <Adafruit_Sensor.h> 

#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();   




 
//TEMP AND HUMIDITY
#define DHTPIN 10
#define DHTPIN1 7
#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE2 DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);
DHT dhtt(DHTPIN1, DHTTYPE2);


//TRACKING
//FLAME DETECTOR
int Analog_Input = A0; 
int Digital_Input = 8;

//TRACKING
int Sensor  =  5;  // Declaration of the sensor input spin

//HALL EFFECT SENSOR
int led = 13 ; // LED on arduino
int digitalPin = 4; // linear Hall magnetic sensor digital interface
int analogPin = A1; // linear Hall magnetic sensor analog interface
int digitalVal ; // digital readings
int analogVal; // analog 

//TILT SWITCH
int led_pin = 13; // Define the LED interface
int switch_pin = 13; // Definition of mercury tilt switch sensor interface
int val;


 
void setup()
{
  
  Serial.begin(9600);
  Serial.println("SATELLITE BASED ON DEBRIS DETECTION USING LiDAR");
  
  pinMode (Analog_Input, INPUT);
  pinMode (Digital_Input, INPUT);
  
  pinMode (Sensor, INPUT)   ;

  pinMode (led, OUTPUT); 
  pinMode (digitalPin, INPUT);

  pinMode(led_pin, OUTPUT);
  pinMode(switch_pin, INPUT);


   if(!accel.begin())

   {

      Serial.println("No valid sensor found");

      while(1);

   }
  
  dht.begin();
}
 

void loop() {
  
   sensors_event_t event; 

   accel.getEvent(&event);

   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");

   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");

   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");

   Serial.println("m/s^2 ");

   delay(500);
  // Two seconds pause between measurements
  delay(2000);
 
  // Humidity is measured
  float h = dht.readHumidity();
  // temperature is measured
  float t = dht.readTemperature();

//    float q = dhtt.readHumidity();
//  // temperature is measured
//  float r = dhtt.readTemperature();
   
  // Checking if the measurements have passed without errors
  // if an error is detected, a error message is displayed here
  if (isnan(h) || isnan(t)) {
    Serial.println("Error reading the inside sensor");
    return;
  }

//    if (isnan(q) || isnan(r)) {
//    Serial.println("Error reading the out side sensor");
//    return;
//  }
 
  // Output to serial console
  Serial.println("-----------------------------------------------------------");
  Serial.print("Humidity Inside the satellite: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature Inside the satellite: ");
  Serial.print(t);
  Serial.print(char(186)); //Output <°> symbol
  Serial.println("C ");
  Serial.println("-----------------------------------------------------------");
  Serial.println(" ");

//   Serial.println("-----------------------------------------------------------");
//  Serial.print("Humidity Outside the satellite: ");
//  Serial.print(q);
//  Serial.print(" %\t");
//  Serial.print("Temperature Outside the satellite: ");
//  Serial.print(r);
//  Serial.print(char(186)); //Output <°> symbol
//  Serial.println("C ");
//  Serial.println("-----------------------------------------------------------");
//  Serial.println(" ");


  float Analog;
  int Digital;
    
  //Actual values are read, converted to the voltage value....
  Analog = analogRead (Analog_Input) * (5.0 / 1023.0); 
  Digital = digitalRead (Digital_Input);
    
  //... and output at this position
  Serial.print ("Analog voltage value:"); Serial.print (Analog, 4); Serial.print ("V, ");
  Serial.print ("Limit value:");
  
  if(Digital==1)
  {
      Serial.println ("Object is in Trajectory");
  }
  else
  {
      Serial.println (" Object out of Trajectory");
  }
  Serial.println ("----------------------------------------------------------------");
  delay (200);

  // Read the digital interface
  digitalVal = digitalRead(digitalPin) ; 
  if (digitalVal == HIGH) // When magnetic field is present, Arduino LED is on
  {
    digitalWrite (led, HIGH);
  }
  else
  {
    digitalWrite (led, LOW);
  }
  
  // Read the analog interface
  analogVal = analogRead(analogPin);
  Serial.println(analogVal); // print analog value
  delay(100);

  //TILT SWITCH

  val = digitalRead(switch_pin); // check mercury switch state
  if(val == HIGH)
  {
    digitalWrite(led_pin, HIGH);
    Serial.println ("TILTED");
  }
  else
  {
    digitalWrite(led_pin, LOW);
    Serial.println ("NOT TILTED");
    
  }
}
