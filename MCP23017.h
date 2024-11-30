#ifndef MCP23017_H
#define MCP23017_H
 
typedef struct MCP23017_config {
  //Configured by the 3 Adress pins A0, A1 & A2
  //A0=GND & A1=GND & A2=GND -> Adress=0x20
  char ADRESS;
  //Defines default pin mode
  //0=INPUT; 1=OUTPUT; 2=INPUT_PULLUP
  unsigned int GPA_MODE[8];
  unsigned int GPB_MODE[8];
  //Defines default values for the output pins
  //0=LOW; 1=HIGH
  unsigned int GPA_VALUE[8];
  unsigned int GPB_VALUE[8];
} MCP23017_config;

enum {GPA0, GPA1, GPA2, GPA3, GPA4, GPA5, GPA6, GPA7, GPB0, GPB1, GPB2, GPB3, GPB4, GPB5, GPB6, GPB7};

class MCP23017 {
private:
  //Configured by the 3 Adress pins A0, A1 & A2
  //A0=GND & A1=GND & A2=GND -> Adress=0x20
  char ADRESS;
  //Defines default pin mode
  //0=INPUT; 1=OUTPUT; 2=INPUT_PULLUP
  unsigned int GPA_MODE[8];
  unsigned int GPB_MODE[8];
  //Defines default values for the output pins
  //0=LOW; 1=HIGH
  unsigned int GPA_VALUE[8];
  unsigned int GPB_VALUE[8];

  char readByte(char ByteAdress);
  void ArrayCpy(unsigned int *Target[8], const unsigned int *A[8]);

public:
  MCP23017(MCP23017_config config);
  void pinMode(unsigned int pin, unsigned int mode);
  void digitalWrite(unsigned int pin, unsigned int val);
  int digitalRead(unsigned int pin);
};

#endif