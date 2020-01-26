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
int echo_pin = 3; //Output for ultrasonic sensor 
int buzzer_pin = 10; // for Buzzer pin  
int time;
int distance; 
int ledState = LOW;
int melody[] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
long preMil = 0;
long intervals = 100; // for first technique for blinking LED 
int timer; // for second technique for blinking LED 
int fanPin = 11;

void setup ( ) {
  Serial.begin (9600); 
  pinMode (trigger_pin, OUTPUT); // Ultrasonic Output Pin  
  pinMode (echo_pin, INPUT); // Ultrasonic Input Pin
  pinMode (buzzer_pin, OUTPUT); // Buzzer Output 
  pinMode (4, OUTPUT); // LED for distance <= 30 
  pinMode (5, OUTPUT); // LED for distance <= 10 and for the last IF ? 
  pinMode (6, OUTPUT); // LED for distance <= 40 
  pinMode (11, OUTPUT); //fan pin 
  
  for ( int j=0; j<8; j++){ //just for fun and testing the buzzer 
    tone(10, melody[j], 200); // tone ( pin , freq , duration )
    delay(300);
   }
}

void loop ( ) {

  unsigned long currentMil = millis();
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger_pin, LOW);
  time = pulseIn (echo_pin, HIGH);
  distance = (time * 0.034) / 2; //Calculating distance((Time x Speed of Sound in Air (340 m/s))/2 
  
  if (distance <= 10) {
    Serial.println ("Distance <= 10  *** ");
    Serial.print ("Distance = ");              
    Serial.println (distance); 
    digitalWrite (fanPin, HIGH); //Fan turn on 
    tone(10, 494, 50); // tone ( pin , freq , duration ) 
    delay (100);
    if( currentMil - preMil > intervals) { //For blinking LED. Fisrt method 
      preMil = currentMil;
      if( ledState == LOW ) 
        ledState = HIGH;
      else 
        ledState = LOW;
      digitalWrite(5 , ledState);

    }
  }
  
  else if ( distance <= 20 ) {
    Serial.print ("Distance <= 20 *** ");
    Serial.print ("Distance = ");  
    Serial.println (distance);                   
    tone(10, c, 200);
    digitalWrite(5, HIGH);
    delay ( 100);
  }
  
  else if ( distance <= 40 ) {
    Serial.print ("Distance <= 40  *** ");
    Serial.print ("Distance= ");  
    Serial.println (distance);        
    tone(10, d, 200);
    digitalWrite(4, HIGH);
    delay (100);
    digitalWrite(4, LOW);
  }
    
  else if ( distance <= 70 ) {
    Serial.print("Distance <= 70  *** ");
    Serial.print ("Distance = ");      
    Serial.println (distance);        
    tone(10, f, 200);
    digitalWrite(6, HIGH);
    delay ( 100);
    digitalWrite(6, LOW);
  }
    
  else {
    
    Serial.print ("Distance = ");              
    Serial.println (distance);        
    digitalWrite (buzzer_pin, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite (11, LOW) ;
    delay (100);        
      } 
  }
