#ifndef MCP23017_CONFIG_H
#define MCP23017_CONFIG_H

typedef struct MCP23017_config {
  //Configured by the 3 Adress pins A0, A1 & A2
  //A0=GND & A1=GND & A2=GND -> Adress=0x20
  char ADDRESS;
  //Defines default pin mode
  //0=INPUT; 1=OUTPUT; 2=INPUT_PULLUP
  uint8_t GPA_MODE[8];
  uint8_t GPB_MODE[8];
} MCP23017_config;

#endif