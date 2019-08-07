/*
 * Adafruit Feather M0 Adalogger
 * SD Card Read and Write Test
 * https://www.adafruit.com/product/2796 
*/

#include <SPI.h>
#include <SD.h>
#define RED 13
#define GREEN 8

File RED_LED;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

int incomingByte = 0;

void loop() {
  if(Serial.available() > 0){
    
    incomingByte = Serial.read();
    
    if(incomingByte == '1'){
      digitalWrite(RED, HIGH);
      RED_LED = SD.open("REDLED.txt", FILE_WRITE);

      if(RED_LED){
        Serial.print("Writing to REDLED.txt...");
        RED_LED.println("RED LED ON.");
        RED_LED.close();
        Serial.println("Done...writing the file");
      }
      else Serial.println("error opening REDLED.txt");
  
     
    }
    else if(incomingByte == '0'){
      digitalWrite(RED, LOW);
      RED_LED = SD.open("REDLED.txt");
      if(RED_LED){
        Serial.println("REDLED.txt:");
        while (RED_LED.available()) {
          Serial.write(RED_LED.read());
        }
        RED_LED.close();
      }
      else Serial.println("error opening REDLED.txt");
      
    }
  }
}
