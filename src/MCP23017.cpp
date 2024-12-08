#include "MCP23017.h"
#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include "MCP23017_config.h"

//=============================================
//    public functions
//=============================================

void MCP23017::begin(MCP23017_config config) {
  //Set I²C Address
  ADDRESS = config.ADDRESS;

  // Reset MCP23017 
  reset();

  //Copy Pin Data
  for (int i = 0; i < 8; i++) {
    GPA_MODE[i] = config.GPA_MODE[i];
    GPB_MODE[i] = config.GPB_MODE[i];
  }
  updatePinMode();
}

void MCP23017::pinMode(uint8_t pin, uint8_t mode) {
  // Input validation 
  if(pin > 15) return;
  if(mode > 2) return;
  
  if (pin < 8) {
    GPA_MODE[pin] = mode;
  } else {
    GPB_MODE[pin-8] = mode;
  }

  updatePinMode();
}

void MCP23017::digitalWrite(uint8_t pin, uint8_t val) {
  // Input validation 
  pin = (pin > 15) ? 15 : pin;
  val = (val >= 1) ? HIGH : LOW;

  if (pin < 8) {
    GPA_VALUE[pin] = val;
    writeBit(GPIOA, pin, val);
  } else {
    GPA_VALUE[pin-8] = val;
    writeBit(GPIOB, pin-8, val);
  }
}

int MCP23017::digitalRead(uint8_t pin) {
  // Input validation 
  pin = (pin > 15) ? 15 : pin;

  if (pin < 8) {
    return (readByte(GPIOA) & (1 << pin)) != 0;
  } else {
    return (readByte(GPIOB) & (1 << (pin - 8))) != 0;
  }
}

void MCP23017::reset() {
  for (int i = 0; i <= 0x15; i++) {
    writeByte(i, (i == IODIRA || i == IODIRB)?255:0);
  }
}

void MCP23017::readAllMem() {
  Serial.println("Reg. Name\tAddress (HEX)\tbit7\tbit6\tbit5\tbit4\tbit3\tbit2\tbit1\tbit0\tSum");
  for (int i = 0; i <= 0x15; i++) {
    byte data = 0x00;
    Wire.beginTransmission(0x20);
    Wire.write(i);
    Wire.endTransmission();
    Wire.requestFrom(0x20, 1);  // request one byte of data from MCP20317
    data = Wire.read();
    Serial.print(RegNames[i]);
    Serial.print((strlen(RegNames[i]) > 7) ? "\t0x" : "\t\t0x");
    Serial.print(i, HEX);
    Serial.print("\t\t");
    for (int i = 0; i < 8; i++) {
      Serial.print((data & (1 << i)) != 0);
      Serial.print("\t");
    }
    Serial.print(data);
    Serial.println();
  }
}

//=============================================
//    private functions
//=============================================

void MCP23017::updatePinMode() {
  byte data = 0;
  byte ByteAddress = 0;

  //GPA IO direction
  ByteAddress = IODIRA;
  data = 0;
  for (int i = 0; i < 8; i++) {
    if (GPA_MODE[i] != OUTPUT) {
      data += 1 << i;
    }
  }
  writeByte(ByteAddress, data);

  //GPA General-Purpose-Pull-Up
  ByteAddress = GPPUA;
  data = 0;
  for (int i = 0; i < 8; i++) {
    if (GPA_MODE[i] == INPUT_PULLUP) {
      data += 1 << i;
    }
  }
  writeByte(ByteAddress, data);

  //GPB IO direction
  ByteAddress = IODIRB;
  data = 0;
  for (int i = 0; i < 8; i++) {
    if (GPB_MODE[i] != OUTPUT) {
      data += 1 << i;
    }
  }
  writeByte(ByteAddress, data);

  //GPB General-Purpose-Pull-Up
  ByteAddress = GPPUB;
  data = 0;
  for (int i = 0; i < 8; i++) {
    if (GPB_MODE[i] == INPUT_PULLUP) {
      data += 1 << i;
    }
  }
  writeByte(ByteAddress, data);
}

void MCP23017::writeBit(byte ByteAddress, uint8_t bitNr, uint8_t val) {
  // Input validation 
  val = (val >= 1) ? HIGH : LOW;
  bitNr = (bitNr > 7) ? 7 : bitNr;

  byte reg = 0;
  byte currVal = 0;
  reg = readByte(ByteAddress);
  currVal = (reg & (1 << bitNr)) != 0;
  if (currVal != val) {
    //chage value
    reg += (currVal < val) ? (1 << bitNr) : -(1 << bitNr);
    writeByte(ByteAddress, reg);
  }
}

int MCP23017::readByte(byte ByteAddress) {
  Wire.beginTransmission(ADDRESS);
  Wire.write(ByteAddress);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 1);
  return Wire.read();
}

void MCP23017::writeByte(byte ByteAddress, byte data) {
  Wire.beginTransmission(ADDRESS);
  Wire.write(ByteAddress);
  Wire.write(data);
  Wire.endTransmission();
}
