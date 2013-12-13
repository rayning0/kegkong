#include <SoftwareSerial.h>


// Create a software serial port!
SoftwareSerial lcd = SoftwareSerial(0,6); 

int flowPin = 2;    //flowmeter pin number
int pulsesCounter = 0;
int previousMeasure = 0;
int counter = 0;

void rpm ()     
{
  pulsesCounter++;  
}

void setup() {
  pinMode(flowPin, INPUT); // Initialize the digital pin as an output
  Serial.begin(9600); // Start serial port
  attachInterrupt(0, rpm, RISING); //Interrupt is attached
  
  lcd.begin(9600);  
  
  // set the size of the display if it isn't 16x2 (you only have to do this once)
  lcd.write(0xFE);
  lcd.write(0xD1);
  lcd.write(16);  // 16 columns
  lcd.write(2);   // 2 rows
  delay(10);       
  // we suggest putting delays after each command to make sure the data 
  // is sent and the LCD is updated.

  // set the contrast, 200 is a good place to start, adjust as desired
  lcd.write(0xFE);
  lcd.write(0x50);
  lcd.write(200);
  delay(10);       
  
  // set the brightness - we'll max it (255 is max brightness)
  lcd.write(0xFE);
  lcd.write(0x99);
  lcd.write(255);
  delay(10);       
  
  // clear screen
  lcd.write(0xFE);
  lcd.write(0x58);
  delay(10);   // we suggest putting delays after each command 

  lcd.print("KEG KONG!");
}

uint8_t red, green, blue;
void loop() {
  
    sei();            //Enable interrupts
  delay (15);
  cli();            //Disable interrupts
  if ((pulsesCounter == previousMeasure) && (pulsesCounter != 0)) {
    counter += 1;
  }

  previousMeasure = pulsesCounter;

  if ((counter == 50) && (pulsesCounter != 0)) { // Send pulses number to Raspberry Pi
    Serial.print("pulses:");
    Serial.println (pulsesCounter, DEC); //Prints the pulses number
    lcd.print("pulses:")
    lcd.print(pulsesCounter, DEC);
    pulsesCounter = 0;
    previousMeasure = 0;
    counter = 0;
  }
  
 // adjust colors 
// for (red = 0; red < 255; red++) {
//  lcd.write(0xFE);
//  lcd.write(0xD0);
//  lcd.write(red); 
//  lcd.write((uint8_t)0);
//  lcd.write(255 - red);
//  delay(10);  // give it some time to adjust the backlight!
// }   
//
// for (green = 0; green < 255; green++) {
//  lcd.write(0xFE);
//  lcd.write(0xD0);
//  lcd.write(255-green); 
//  lcd.write(green);
//  lcd.write((uint8_t)0);
//  delay(10);  // give it some time to adjust the backlight!
// }   
//
// for (blue = 0; blue < 255; blue++) {
//  lcd.write(0xFE);
//  lcd.write(0xD0);
//  lcd.write((uint8_t)0); 
//  lcd.write(255-blue);
//  lcd.write(blue);
//  delay(10);  // give it some time to adjust the backlight!
 }   
}


