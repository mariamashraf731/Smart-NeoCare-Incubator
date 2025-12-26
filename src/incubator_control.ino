#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(2,3); // RX, TX
#include <dht.h>

int Incoming_value = 1;  // The Value which comes from Mobile App

//Variable of thermistor

int ThermistorPin = A4;
int Vo;
float R1 = 10000;
float logR2, R2, T;
double Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int Red_temp=8;
int White_temp=9;

int piezo=13;

//Variable of sound

#define MIC A2
int sig=0;
int led1=0;
int led2=1;
int led3=4;
int led4=5;

//Variable of relay

int IN2=12;
int LED_FAN = 7; 

//Variable of humidity

dht DHT;
#define DHT11_PIN A3
int Red_hum=10;
int White_hum=11;

int temp;
int hum;

//Variable of heartbeat

int x=0;
int lastx=0;
int lasty=0;
int LastTime=0;
int ThisTime;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM=0;
#define UpperThreshold 560
#define LowerThreshold 500

//Variable of FSR

// Define FSR pin:
#define fsrpin A5
//Define variable to store sensor readings:
int fsrreading; //Variable to store FSR value


void setup() {
  //thermistor
  Bluetooth.begin (9600);   // Open communication between bluetooth module and arduino 
  Serial.begin(9600);      // Open communication between Arduino module and Serial Monitor
  pinMode(Red_temp,OUTPUT);
  pinMode(White_temp,OUTPUT); 
  
  // Alarms of Sound detector
  pinMode(led_Green,OUTPUT);
  pinMode(led_Yellow,OUTPUT);
  pinMode(led_Red,OUTPUT);
  pinMode(piezo,OUTPUT);
  
  //relay
  pinMode(IN2,OUTPUT);      // Relay for Fan
  pinMode(LED_FAN , OUTPUT);// Alarm for Fan
  
  //Alarms of humidity
  pinMode(Red_hum,OUTPUT);
  pinMode(White_hum,OUTPUT);

}

//sound
void led() {
  sig=analogRead(MIC)*50;
  if (sig>2000) {digitalWrite(2,HIGH);} else{digitalWrite(2,LOW);}
  if (sig>2500) {digitalWrite(3,HIGH);} else{digitalWrite(3,LOW);}
  if (sig>3000) {digitalWrite(4,HIGH);} else{digitalWrite(4,LOW);}
  }

void loop() {
   // thermistor
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = abs( T - 273.15);
  Tf = abs((Tc * 9.0)/ 5.0 + 32.0); 

  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");   
    if(Tc<35){                     //Indication of hypothermia
    digitalWrite(Red_temp,HIGH); 
    digitalWrite(White_temp,LOW);}
    else if(35 < Tc < 37){         // Normal range of temperature
      digitalWrite(Red_temp,LOW);
      digitalWrite(White_temp,LOW);
      }
     else{                        // Indication of hyperthermia
      digitalWrite(Red_temp,LOW); 
      digitalWrite(White_temp,HIGH);
      }
      
   //sound
   led(); // Function for Sound detector
  //relay 
  digitalWrite (IN2 , HIGH); // Fan is on
  
  //humidity
  
 int readData = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(2000);

 
  if (DHT.humidity < 60){
    digitalWrite(Red_hum,HIGH);
    digitalWrite(White_hum,LOW);
    }
   else if (60< DHT.humidity <70){
    digitalWrite(Red_hum,LOW);
    digitalWrite(White_hum,LOW);
    }
   else {
    digitalWrite(Red_hum,LOW);
    digitalWrite(White_hum,HIGH);
    }
    
    //heartbeat
    if(x>127)  
  { 
    x=0;
    lastx=x;
  }
  ThisTime=millis();
  int value=analogRead(A0);
  int y=60-(value/16);
  lasty=y;
  lastx=x;
  // calc bpm
  if(value>UpperThreshold)
  {
    if(BeatComplete)
    {
      BPM=ThisTime-LastTime;
      BPM=int(60/(float(BPM)/1000));
      BPMTiming=false;
      BeatComplete=false;
      tone(12,1000,250);
      digitalWrite(piezo,HIGH); 
    }
    if(BPMTiming==false)
    {
      LastTime=millis();
      BPMTiming=true;
    }
  }
  if((value<LowerThreshold)&(BPMTiming))
    BeatComplete=true;
    // display bpm
  x++;
  Serial.println(analogRead(A0));

  //FSR
  
  // Read the FSR pin and store the output as fsrreading:
  fsrreading = analogRead(fsrpin);
  // Print the fsrreading in the serial monitor:
  // Print the string "Analog reading = ".
  Serial.print("FSR reading = ");
  // Print the fsrreading:
  Serial.print(fsrreading);

  // For Mobile Application
  if(Bluetooth.available() > 0)  
  {
    Incoming_value = Bluetooth.read(); 
  }
  
  switch (Incoming_value)
   {
  case 1 : 
  Temp;
  break;
  case 0 : 
  Hum;
  break;
   } 
}
void Temp ()
{
 Bluetooth.print(DHT.temperature);  // Sending Temperature to bluetooth connected to bluetooth module
  delay(400); 
}

void Hum ()
{
 Bluetooth.print(DHT.humidity);  // Sending Humidity  to bluetooth connected to bluetooth module
  delay(400); 
}
