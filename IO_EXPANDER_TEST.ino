#include "Wire.h"
#include "MCP23017.h"

 

MCP23017 IOEX(MCP23017_config{
  .ADRESS = 0x20,
  .GPA_MODE = {OUTPUT},
  .GPB_MODE = {OUTPUT},
  .GPA_VALUE = {LOW},
  .GPB_VALUE = {LOW}
});

void setup() {
  Serial.begin(115200);
  Wire.begin();  // wake up I²C bus
  delay(200);
  Serial.println("Wilkommen!\nReading all Memory registers from Chip!\n");
  readAllMem();


  // //Set A GPIO Pins to OUTPUT
  // Wire.beginTransmission(0x20);
  // Wire.write(0x0);
  // Wire.write(0x0);
  // Wire.endTransmission();
  // readAllMem();
  // delay(1000);
}

void loop() {
  // Wire.beginTransmission(0x20);
  // Wire.write(0x12);
  // Wire.write(0x255);
  // Wire.endTransmission();
  // readAllMem();
  // delay(1000);
  // Wire.beginTransmission(0x20);
  // Wire.write(0x12);
  // Wire.write(0);
  // Wire.endTransmission();
  // readAllMem();
  // delay(1000);
}

void readAllMem() {
  Serial.print("\n\n");
  for (int i = 0; i < 0x15; i++) {
    byte inputs = 00000000;
    Wire.beginTransmission(0x20);
    Wire.write(i);
    Wire.endTransmission();
    Wire.requestFrom(0x20, 1);  // request one byte of data from MCP20317
    inputs = Wire.read();
    Serial.print("0x");
    Serial.print(i, HEX);
    Serial.print(":\t");
    Serial.println(inputs, BIN);  // display the contents of the GPIOB register in binary
  }
}