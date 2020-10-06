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
int sensor1 = 8; // PIR Sensor1’s Data OUT Pin is connected to Arduino’s Digital I/O Pin 8.
int sensor2 = 10; // PIR Sensor1’s Data OUT Pin is connected to Arduino’s Digital I/O Pin 10.
int LDR = 12;  // LDR is connected to Arduino’s Digital I/O Pin 12.
unsigned long t = 0;

void setup() {

    // Set parameters for the RTC object to use and start the
    //   real time clock (RTC)
    rtc.begin();

    // Set the current date/time here: year,month,day,hour,minutes,seconds
    RTC.adjust(DateTime(2020, 10, 6, 10, 00, 00));


    pinMode(in1, OUTPUT);
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(LDR,INPUT); // LDR is connected to this pin

    digitalWrite(in1, HIGH);

    Serial.begin(9600);

}

void loop() {

   // Turn on lights on non-weekends in college, prep and night
	if ((weekday() > 1 || weekday() < 7)) {
	 
	 		if (hour() >= 6 && hour() <= 14 && minute()==45)
	        	digitalWrite(in1, LOW);

            // If its dark, turn on lights anyway
                else if (digitalRead(LDR)==0)
                    digitalWrite(in1, LOW);

	        else if (hour() >= 20 && hour() <= 23)
	        	digitalWrite(in1,LOW);
	        else if (hour() > 23 || hour() < 6 )
	        	digitalWrite(in1,LOW);
	        else
	        	digitalWrite(in1,HIGH);

	}

    else {
    	// weekends day time
    	if (hour() >= 6 && hour() <= 19)
        	digitalWrite(in1, HIGH);

        else
        	digitalWrite(in1, LOW);

    }

       
}
