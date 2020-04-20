#include "pitches.h"
#define  c     3830    // 261 Hz
#define  d     3400    // 294 Hz
#define  e     3038    // 329 Hz
#define  f     2864    // 349 Hz
#define  g     2550    // 392 Hz
#define  a     2272    // 440 Hz
#define  b     2028    // 493 Hz
#define  C     1912    // 523 Hz
#define  R     0

int trigger_pin = 2; //Output for ultrasonic sensor 
int echo_pin = 3; //Input for ultrasonic sensor 
int red_Led = 4;
int yellow_Led = 5;
int green_Led = 6;
int buzzer_pin = 7;
int fan_Pin = 8;

int time; //For measuring distance using Ultrasonic
int distance;//For measuring distance using Ultrasonic

bool ledState = false;//For blinking LED
long preMil = 0;//For blinking LED
long intervals = 100; //Time for blinking LED

int melody[] = { c, d, e, f, g, 0, a, b }; //buzzer test... just for fun!

void setup ( ) {
  Serial.begin (9600); 
  pinMode (trigger_pin, OUTPUT); 
  pinMode (echo_pin, INPUT); 
  pinMode (red_Led, OUTPUT); 
  pinMode (yellow_Led, OUTPUT); 
  pinMode (green_Led, OUTPUT); 
  pinMode (buzzer_pin, OUTPUT); 
  pinMode (fan_Pin, OUTPUT); 
  
  for ( int j=0; j<8; j++){ //Testing the buzzer 
    tone(buzzer_pin, melody[j], 80); // tone ( pin , freq , duration )
    if ( 3 < j < 7 ){ //Testing all the LEDs
      digitalWrite(j,HIGH);
    }
    delay(150);
   }
}

void loop ( ) {
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds (10);//High level signal is sent for 10µs using Trigger (Slides!)
  digitalWrite (trigger_pin, LOW);
  time = pulseIn (echo_pin, HIGH);
  distance = (time * 0.034) / 2; //Calculating distance -> ( (Time x Speed of Sound in Air (340 m/s) )/2 
  
  unsigned long currentMil = millis(); //returns the number of milliseconds the current sketch has been running since the last reset
  if (distance <= 5) {
    Serial.println ("Distance <= 5  *** ");
    Serial.print ("Distance = ");              
    Serial.println (distance); 
    tone(buzzer_pin, g, 50); // tone ( pin , freq , duration ) 
    digitalWrite (fan_Pin, LOW); //Fan is turned on 
    delay (100);
    if (currentMil - preMil > intervals) { //For LED blinking
      preMil = millis();
      ledState = !ledState;
      digitalWrite(red_Led , ledState);
    }
  }
  
  else if ( distance <= 10 ) {
    Serial.print ("Distance <= 10 *** ");
    Serial.print ("Distance = ");  
    Serial.println (distance);                   
    tone(buzzer_pin, g, 200);
    digitalWrite(green_Led, LOW);
    digitalWrite(yellow_Led, LOW);
    digitalWrite(red_Led, HIGH);
    delay ( 100);
  }
  
  else if ( distance <= 20 ) {
    Serial.print ("Distance <= 20  *** ");
    Serial.print ("Distance= ");  
    Serial.println (distance);        
    tone(buzzer_pin, e, 200);
    digitalWrite(red_Led, LOW);
    digitalWrite(green_Led, LOW);
    digitalWrite(yellow_Led, HIGH);
    delay (100);
  }
    
  else if ( distance <= 40 ) {
    Serial.print("Distance <= 40  *** ");
    Serial.print ("Distance = ");      
    Serial.println (distance);        
    tone(buzzer_pin, c, 200);
    digitalWrite(red_Led, LOW);
    digitalWrite(yellow_Led, LOW);
    digitalWrite(green_Led, HIGH);
    delay ( 100);
  }
    
  else {
    Serial.print ("Distance = ");              
    Serial.println (distance);        
    digitalWrite (buzzer_pin, LOW);
    digitalWrite(red_Led, LOW);
    digitalWrite(yellow_Led, LOW);
    digitalWrite(green_Led, LOW);
    digitalWrite (fan_Pin, HIGH) ;
    delay (100);        
      } 
  }
