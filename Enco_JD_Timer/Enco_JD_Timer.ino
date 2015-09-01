// TestEnco.ino  
#include <Arduino.h>  //<avrio.h>
// Test la routine encodeur
#include "Debug.h"
#include "Enco.h"
#include "Inter.h"

void setup() {  // initialisation
  SetupEnco();
  SetupDebug();
  SetupInter();
  DDRC = 0xFF;
}
void loop() {
  pos=0;
  AvG; delay (600); 
  StopG; delay (1000); 
  pos=0;
  RecG; delay (600); 
  StopG; delay (1000); 

}

