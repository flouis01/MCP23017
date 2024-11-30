#include "MCP23017.h"
#include <Arduino.h>
#include <Wire.h>
 

MCP23017::MCP23017(MCP23017_config config) {
  ADRESS = config.ADRESS;

  ArrayCpy(GPA_MODE, config.GPA_MODE);
  ArrayCpy(GPB_MODE, config.GPB_MODE);
  char GPA_MODE_Byte = 0;
  for (int i = 0; i < 7; i++) {
    
  }
  Wire.beginTransmission(ADRESS);
  Wire.write(0x0);
  Wire.write(0x0);
  Wire.endTransmission();
  ArrayCpy(GPA_VALUE, config.GPA_VALUE);
  ArrayCpy(GPB_VALUE, config.GPB_VALUE);
}

void MCP23017::pinMode(unsigned int pin, unsigned int mode) {
}

void MCP23017::digitalWrite(unsigned int pin, unsigned int val) {
}

int MCP23017::digitalRead(unsigned int pin) {
}

char MCP23017::readByte(char ByteAdress) {
  Wire.beginTransmission(ADRESS);
  Wire.write(ByteAdress);
  Wire.endTransmission();
  return Wire.requestFrom(ADRESS, 1);
}

void MCP23017::ArrayCpy(unsigned int *Target[8], const unsigned int *A[8]) {
  for (int i = 0; i < 8; i++) {
    target[i] = A[i];
  }
}
