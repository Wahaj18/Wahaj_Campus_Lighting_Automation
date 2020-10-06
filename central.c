#include <Wire.h>
#include "RTClib.h"
#include <TimeLib.h>

RTC_DS1307 RTC;

// Include the real time clock header for the DS3231
//   and define a DS3231 object
#include <DS3231.h>
// define a DS3231 object rtc; the DS3231 uses I2C interface
DS3231 rtc(A4, A5); // SDA  to A4, and SCL to A5

int in1 = 9; // The IN1 pin of the Relay Module is connected to Pin 9 of Arduino
int sensor = 8; // PIR Sensor’s Data OUT Pin is connected to Arduino’s Digital I/O Pin 8. 
int LDR = 12; // LDR is connected to Arduino’s Digital I/O Pin 12.
unsigned long t=0;
+
void setup() {

 // Set parameters for the RTC object to use and start the
 //   real time clock (RTC)
 rtc.begin();

 // Set the current date/time here: year,month,day,hour,minutes,seconds
 RTC.adjust(DateTime(2020,10,6,10,00,00));
 
  pinMode(in1, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(LDR,INPUT); // LDR is connected to this pin
  
  digitalWrite(in1,HIGH);
 
Serial.begin(9600);

}

void loop() {

	// Turn on lights during College time on non-weekends
	if ((hour() == 6 && minute() == 45) && (weekday() > 1 || weekday() < 7)) {
		digitalWrite(in1,LOW);
	} 

	// If its dark, turn on lights anyway
                else if (digitalRead(LDR)==0)
                    digitalWrite(in1, LOW);
	
	// 		Turn on during prep
	else if (hour() >= 20 && hour <= 23)
		digitalWrite(in1,LOW);
		
		// 	else put it on PIR
	else if (weekday() > 1 || weekday() < 7){
			digitalWrite(in1,HIGH);
			if(digitalRead(sensor)==HIGH)
			{
			   t=millis();
			   while(millis()<(t+5000))
			   {
			   digitalWrite(in1,LOW);
			     if((millis()>(t+2300))&&(digitalRead(sensor)==HIGH))
			      {
			       t=millis();
			      }
			   }
  			}
	}

	// Weekends: OFF on day time (7am-7pm) and PIR on night (7pm afterwards)
	else if (weekday() > 6 || weekday() < 2) {
		if (hour() >= 7 && hour() <= 19)
			digitalWrite(in1,HIGH);
		// If its dark, turn on lights anyway
                else if (digitalRead(LDR)==0)
                    digitalWrite(in1, LOW);
		else {
			digitalWrite(in1,HIGH);
			if(digitalRead(sensor)==HIGH)
			{
			   t=millis();
			   while(millis()<(t+5000))
			   {
			   digitalWrite(in1,LOW);
			     if((millis()>(t+2300))&&(digitalRead(sensor)==HIGH))
			      {
			       t=millis();
			      }
			   }
  			}
		}
	}

}
