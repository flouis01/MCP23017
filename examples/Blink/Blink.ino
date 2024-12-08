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
    .GPA_MODE = { OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT },
    .GPB_MODE = { OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT } 
  }));

  // Reads all memory-registers of the MCP23017 and prints them to a table in the serial monitor 
  IOEX.readAllMem();
}

void loop() {
  // Loop through all 16 Pins of the MCP23017
  for(int pin = 0; pin < 16; pin++){
    // Set Pin HIGH and wait 500ms
    IOEX.digitalWrite(pin, HIGH);
    Serial.print("Pin ");
    Serial.print(pin);
    Serial.println(" HIGH");
    delay(500);

    // Set Pin Low and wait 500ms
    IOEX.digitalWrite(pin, LOW);
    Serial.print("Pin ");
    Serial.print(pin);
    Serial.println(" LOW");
    delay(500);
  }
}