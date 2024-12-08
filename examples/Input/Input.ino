#include <Wire.h>
#include <MCP23017.h>

// Declaring the IOEX object
MCP23017 IOEX;

void setup() {
  // Initializing Serial bus
  Serial.begin(115200);

  // Initializing I²C bus
  Wire.begin();

  // Initializing The IOEX object with the given address and Pinmodes
  IOEX.begin((MCP23017_config{
    .ADDRESS = 0x20,
    .GPA_MODE = { INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT },
    .GPB_MODE = { INPUT_PULLUP, INPUT_PULLUP, INPUT_PULLUP, INPUT_PULLUP, INPUT_PULLUP, INPUT_PULLUP, INPUT_PULLUP, INPUT_PULLUP } 
  }));

  // Reads all memory-registers of the MCP23017 and prints them to a table in the serial monitor 
  IOEX.readAllMem();
}

void loop() {
  // Loop through all 16 Pins of the MCP23017
  Serial.print("\n\n");
  for(int pin = 0; pin < 16; pin++){
    // Print digitalRead(pin) to the serial monitor 
    Serial.print("Pin ");
    Serial.print((pin < 10)?"0":"");
    Serial.print(pin);
    Serial.print(" = ");
    Serial.println(IOEX.digitalRead(pin));
  }
  delay(1000);
}