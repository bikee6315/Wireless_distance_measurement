//Data pin of RF Receiver module is connected to pin 11 of the Arduino Uno Board.
#include <LiquidCrystal.h>
#include <VirtualWire.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
// LED's
int ledPin = 13;
// Sensors 
int Data;
// RF Transmission container
char Distance[4]; 
void setup() {
Serial.begin(9600);
lcd.begin(16, 2);
lcd.print("ECE Deptt.");
lcd.setCursor(0, 1);
  // sets the digital pin as output
pinMode(ledPin, OUTPUT);      
pinMode(9, OUTPUT);
pinMode(8, OUTPUT);
// VirtualWire
// Initialise the IO and ISR
// Required for DR3100
vw_set_ptt_inverted(true); 
// Bits per sec
vw_setup(2000);     
// Start the receiver PLL running
vw_rx_start();       
} // END void setup

void loop(){
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
// Non-blocking
if (vw_get_message(buf, &buflen))
 {
int i;
        // Turn on a light to show received good message 
digitalWrite(13, true); 
        // Message with a good checksum received, dump it. 
for (i = 0; i<buflen; i++)
    {            
          // Fill Sensor1CharMsg Char array with corresponding 
          // chars from buffer.   
          Distance[i] = char(buf[i]);
    }
Distance[buflen] = '\0';
 // Convert Sensor1CharMsg Char array to integer
 Data = atoi(Distance);
// DEBUG 
Serial.print("distance = ");
Serial.print(Data);
Serial.println(" cm ");
lcd.setCursor(0, 2);
lcd.print("Distance = ");
lcd.print(Data); // change the analog out value:
lcd.print("cm ");         
    }
}
