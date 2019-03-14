
//Data pin of RF Transmitter module is connected to pin 12 of the Arduino Uno Board.

#include <VirtualWire.h>
int trigPin = 2;
int echoPin = 4;
char Distance[4]; 
void setup() {
Serial.begin(9600); 
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);  
vw_setup(2000);   
}
void loop() 
{
long duration, distance, cm;
pinMode(trigPin, OUTPUT);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
cm=distance+1;
Serial.print(cm);
Serial.print("cm");
Serial.println();
delay(100);
//Convert integer value to character value
itoa(cm,Distance,10);
digitalWrite(13, true); // Turn on a light to show transmitting
vw_send((uint8_t *)Distance, strlen(Distance));
vw_wait_tx(); // Wait until the whole message is gone
digitalWrite(13, false); // Turn off a light after transmission
delay(200); 
}

