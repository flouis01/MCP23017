#include <Wire.h>
#include "MCP23017.h"

MCP23017 IOEX;



void setup() {
  Serial.begin(115200);
  Wire.begin();
  IOEX.begin((MCP23017_config{
    .ADRESS = 0x20,
    .GPA_MODE = { OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT },
    .GPB_MODE = { OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT } 
  }));
  Serial.println("Wilkommen!\n");
  delay(1000);
  IOEX.readAllMem();
  delay(1000);
}

void loop() {

  for(int i = 0; i < 8; i++){
    IOEX.digitalWrite(i, HIGH);
    Serial.print("Pin ");
    Serial.print(i);
    Serial.println(" HIGH");
    delay(500);
    IOEX.digitalWrite(i, LOW);
    Serial.print("Pin ");
    Serial.print(i);
    Serial.println(" LOW");
  }
}