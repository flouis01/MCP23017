#ifndef MCP23017_H
#define MCP23017_H
#include <Arduino.h>


// MCP23017 Regestry List
#define IODIRA 0x00  //I/O DIRECTION REGISTER: 0=OUT; 1=IN
#define IODIRB 0x01
#define IPOLA 0x02  //INPUT POLARITY PORT REGISTER: 0=Logical equal; 1=Logical opposite
#define IPOLB 0x03
#define GPINTENA 0x04  //INTERRUPT-ON-CHANGE PINS: 0=Disabled; 1=Enabled
#define GPINTENB 0x05
#define DEFVALA 0x06  //DEFAULT VALUE REGISTER
#define DEFVALB 0x07
#define INTCONA 0x08  //INTERRUPT-ON-CHANGE CONTROL REGISTER
#define INTCONB 0x09
#define IOCON 0x0A  //I/O EXPANDER CONFIGURATION REGISTER
//efine IOCON 0x0B
#define GPPUA 0x0C  // GPIO PULL-UP RESISTOR REGISTER: 0=no Pullup; 1=Pullup
#define GPPUB 0x0D
#define INTFA 0x0E  //INTERRUPT FLAG REGISTER
#define INTFB 0x0F
#define INTCAPA 0x10  //INTERRUPT CAPTURED VALUE FOR PORT REGISTER
#define INTCAPB 0x11
#define GPIOA 0x12  //GENERAL PURPOSE I/O PORT REGISTER: 0=LOW; 1=HIGH
#define GPIOB 0x13
#define OLATA 0x14  //OUTPUT LATCH REGISTER: 0=LOW; 1=HIGH
#define OLATB 0x15

// MCP23017 Pin List
#define GPA0 0
#define GPA1 1
#define GPA2 2
#define GPA3 3
#define GPA4 4
#define GPA5 5
#define GPA6 6
#define GPA7 7
#define GPB0 8
#define GPB1 9
#define GPB2 10
#define GPB3 11
#define GPB4 12
#define GPB5 13
#define GPB6 14
#define GPB7 15


typedef struct MCP23017_config {
  //Configured by the 3 Adress pins A0, A1 & A2
  //A0=GND & A1=GND & A2=GND -> Adress=0x20
  char ADRESS;
  //Defines default pin mode
  //0=INPUT; 1=OUTPUT; 2=INPUT_PULLUP
  uint8_t GPA_MODE[8];
  uint8_t GPB_MODE[8];
} MCP23017_config;

class MCP23017 {
private:
  //Configured by the 3 Adress pins A0, A1 & A2
  //A0=GND & A1=GND & A2=GND -> Adress=0x20
  char ADRESS;

  //Defines default pin mode
  //0=INPUT; 1=OUTPUT; 2=INPUT_PULLUP
  uint8_t GPA_MODE[8];
  uint8_t GPB_MODE[8];

  //Defines default values for the output pins
  //0=LOW; 1=HIGH
  uint8_t GPA_VALUE[8];
  uint8_t GPB_VALUE[8];

  void updatePinMode();

  //names of all memory-registers (Used by the ReadAllMem function)
  const char RegNames[22][10] = {
    "IODIRA",
    "IODIRB",
    "IPOLA",
    "IPOB",
    "GPINTENA",
    "GPINTENB",
    "DEFVALA",
    "DEFVALB",
    "INTCONA",
    "INTCONB",
    "IOCON",
    "IOCON",
    "GPPUA",
    "GPPUB",
    "INTFA",
    "INTFB",
    "INTCAPA",
    "INTCAPB",
    "GPIOA",
    "GPIOB",
    "OLATA",
    "OLATB"
  };

  void writeBit(byte ByteAdress, uint8_t bitNr, uint8_t val);

  int readByte(byte ByteAdress);

  void writeByte(byte ByteAdress, byte data);


public:

  // Begins comunication with the MCP23017, resets the MCP23017 and make basic Settings (Pinmode)
  void begin(MCP23017_config config);

  // Changes the pinmode of a specified pin
  void pinMode(uint8_t pin, uint8_t mode);

  // Sets the digital output of a specified pin
  void digitalWrite(uint8_t pin, uint8_t val);

  // Returns the digital high low state of a specified pin
  int digitalRead(uint8_t pin);

  // Reads all memory-registers and prints them to the Serial Monitor in a table format
  void readAllMem();

  // Resets the Chip
  void reset();
};

#endif