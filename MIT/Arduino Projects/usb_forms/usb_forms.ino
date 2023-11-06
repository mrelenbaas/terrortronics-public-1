/*
   Title: ultrasonic_sensor file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the Arduino License.
*/

const int LedPin = 2;  
int ledState = 0;  

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:ultrasonic_sensor,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

void setup()  
{   
  pinMode(LedPin, OUTPUT);  
  digitalWrite(LedPin, HIGH);
  delay(1000);
    
  Serial.begin(9600);    
}  

/**
   The main function.
*/
void loop()  
{   
    char receiveVal;     
     
    if(Serial.available() > 0)  
    {          
        receiveVal = Serial.read();  
          
       if(receiveVal == '1')      
          ledState = 1;     
       else  
          ledState = 0;       
    }     
        
    digitalWrite(LedPin, ledState);   
    Serial.println(ledState);

    if (Serial.available() > 0) {
    // WARNING: Remember to consume the incoming bytes.
    // The error does not occur when using the usb.c or usb.py files.
    // The error does occur when reading/writing in a PyGame application.
    incomingMessage = Serial.read();
    switch (incomingMessage) {
      case startMessage:
        start();
        break;
      case resetMessage:
        reset();
        break;
      default:
        break;
    }
  }
        
    delay(50);      
}

void reset() {
  Serial.println("reset()");
}

void start() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}
