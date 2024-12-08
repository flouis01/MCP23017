#include <Wire.h>
#include <MCP23017.h>

// Declaring the IOEX object
MCP23017 IOEX;

char pinModes[3][13] = {"INPUT", "OUTPUT", "INPUT_PULLUP"};

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
  Serial.print("\n\n");
  Serial.println("Available Methods:");
  Serial.println("[0] pinMode");
  Serial.println("[1] digitalread");
  Serial.println("[2] digitalWrite");
  Serial.println("[3] readAllMem");

  switch (getFromSerial("", 0, 3)) {
  case 0:{ // pinMode
    // Select Pin
    Serial.println("pinMode(pin, mode):");
    Serial.println("Define: pin [0-15]");
    int pin = getFromSerial("", 0, 15);

    //Select Mode
    Serial.print("pinMode");
    Serial.print(pin);
    Serial.println(", mode):");
    Serial.println("Define: mode ");
    Serial.println("[0] INPUT");
    Serial.println("[1] OUTPUT");
    Serial.println("[2] INPUT_PULLUP");
    int mode = getFromSerial("", 0, 2);

    //Adjust Pinmode
    IOEX.pinMode(pin, mode);

    // Print to serial monitor
    Serial.print("The pinMode of pin ");
    Serial.print(pin);
    Serial.print(" is now set to ");
    Serial.println(pinModes[mode]);
  }break;
  case 1:{ // digitalRead
    // Select Pin
    Serial.println("digitalRead(pin):");
    Serial.println("Define: pin [0-15]");
    int pin = getFromSerial("", 0, 15);

    // Print to serial monitor
    Serial.print("The value of pin ");
    Serial.print(pin);
    Serial.print(" is ");
    Serial.println(IOEX.digitalRead(pin));
  }break;
  case 2:{ // digitalWrite
    // Select Pin
    Serial.println("digitalWrite(pin, value):");
    Serial.println("Define: pin [0-15]");
    int pin = getFromSerial("", 0, 15);
    
    // Select Value
    Serial.print("digitalWrite(");
    Serial.print(pin);
    Serial.print(", value):");
    Serial.println("Define: value [0-1]");
    int value = getFromSerial("", 0, 1);

    IOEX.digitalWrite(pin, value);
    // Print to serial monitor
    Serial.print("The value of pin ");
    Serial.print(pin);
    Serial.print(" is now ");
    Serial.println(value);
  }break;
  case 3:{ // readAllMem
    IOEX.readAllMem();
  }break;
  }
}

int getFromSerial(String options, int min, int max){
  Serial.println(options);

    // Wait for input
    while (Serial.available() < 1) {}
    int input = 0;
    input = Serial.readStringUntil('\n').toInt();
    Serial.println(input);

    // Input validation
    if(input < min || input > max){
      Serial.print(input);
      Serial.println(" is no Option.");
      return getFromSerial(options, min,max);
    }

  return input;
} 