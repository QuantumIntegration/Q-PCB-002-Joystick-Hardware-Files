// Tim Lubes
// Quantum Integration, 2021

#include "Wire.h"

// uncomment for debug information
// #define DEBUG

#ifdef DEBUG
  #define DEBUG_P(...) Serial.print(__VA_ARGS__)
  #define DEBUG_PLN(...) Serial.println(__VA_ARGS__)
#else
  #define DEBUG_P(...)
  #define DEBUG_PLN(...)
#endif

#define JOYSTICK_1_X   A0
#define JOYSTICK_1_Y   A1
#define JOYSTICK_1_SW  2
#define JOYSTICK_2_X   A2 
#define JOYSTICK_2_Y   A3
#define JOYSTICK_2_SW  3  
#define TACTILE_SW     4  

struct {
  uint16_t joystick_1_x;  
  uint16_t joystick_1_y;         
  bool joystick_1_sw;
  uint16_t joystick_2_x;  
  uint16_t joystick_2_y;         
  bool joystick_2_sw;
  bool tactile_sw;         
} joystick_output;            // saves the joystick output data 
              
void setup() {
  Serial.begin(115200); 
  pinMode(JOYSTICK_1_X, INPUT);
  pinMode(JOYSTICK_1_Y, INPUT);
  pinMode(JOYSTICK_1_Y, INPUT); 
  pinMode(JOYSTICK_2_X, INPUT);
  pinMode(JOYSTICK_2_Y, INPUT);
  pinMode(JOYSTICK_2_Y, INPUT);
  pinMode(TACTILE_SW, INPUT);
  
  Wire.begin();
}

void loop() {
  
  joystick_output.joystick_1_x = analogRead(JOYSTICK_1_X);
  joystick_output.joystick_1_y = analogRead(JOYSTICK_1_Y);
  joystick_output.joystick_1_sw  = !digitalRead(JOYSTICK_1_SW);  // Invert the pulldown switch
  joystick_output.joystick_2_x  = analogRead(JOYSTICK_2_X);
  joystick_output.joystick_2_y  = analogRead(JOYSTICK_2_Y);
  joystick_output.joystick_2_sw =  !digitalRead(JOYSTICK_2_SW);  // Invert the pulldown switch
  joystick_output.tactile_sw = digitalRead(TACTILE_SW);

  DEBUG_P(joystick_output.joystick_1_x);
  DEBUG_P(",");
  DEBUG_P(joystick_output.joystick_1_y);
  DEBUG_P(",");
  DEBUG_P(joystick_output.joystick_1_sw);
  DEBUG_P(",");
  DEBUG_P(joystick_output.joystick_2_x);
  DEBUG_P(",");
  DEBUG_P(joystick_output.joystick_2_y);
  DEBUG_P(",");
  DEBUG_P(joystick_output.joystick_2_sw); 
  DEBUG_P(",");
  DEBUG_PLN(joystick_output.tactile_sw); 
  
  Wire.beginTransmission(0x22);
  Wire.write((uint8_t*) &joystick_output, sizeof(joystick_output));
  Wire.endTransmission();
    
  delay(100);
}
