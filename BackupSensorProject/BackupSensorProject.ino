//====================== Initialization Declarations ======================

//== Ultrasonic Distance Sensor ==
#define trigPin 10
#define echoPin 13
float duration; //Duration: duration of signal we get back
int distance;
unsigned long interval = 0;

//== LCD == 
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//== LED ==
int ledPin = 8;

//==Piezo==
const int buzzer = 9;

//== Other Included Libraries == 
#include <math.h>

//====================== Setup ============================================
void setup(){
  Serial.begin(9600);

  pinMode(ledPin,OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT);
}

// ============= Loop ====================
void loop(){  
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);         //Sent for 2 microseconds. Doesn't matter how long really
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);         // Search for the pulse sent out 
  distance = int((duration/2)*0.0343);      // Find distnace with speed of sound and this constant.

  if(distance >= 400 || distance <= 2){     // Distance sensor only works for distances between 400cm and 2 cm
    lcd.clear();
    lcd.print("Out of range");
  }
  else{
    lcd.clear();

    if(distance < 10){
      lcd.print("00" + String(distance) + " CM");
    }
    else if (distance >= 10 && distance <= 99){
      lcd.print("0" + String(distance) + " CM");
    }
    else{
      lcd.print(String(distance) + " CM");
    }
    
    //=================

    if (distance >= 300 && distance < 400){       
      interval = 500;                             
    }                                             
    else if (distance >= 200 && distance < 300){
      interval = 400;
    }
    else if(distance >= 100 && distance < 200){
      interval = 300;
    }
    else if(distance >= 50 && distance < 100){
      interval = 200;
    }
    else if(distance >= 3 && distance  < 50){
      interval = 100;
    }

    digitalWrite(ledPin,HIGH);
    tone(buzzer,1000);
    delay(interval);
    digitalWrite(ledPin,LOW);
    noTone(buzzer);
    delay(interval); 
  }
}

