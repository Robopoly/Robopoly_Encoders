// Enco.h
#include <Arduino.h>  //<avrio.h>
//Câblé sur LC2
#define bP1  2 // PORTD  
#define bP2  3
#define   P1On  !(PIND&(1<<bP1)) 
#define   P2On  !(PIND&(1<<bP2))
#define bRecG 4 // PORTD
#define bAvG 5
#define   AvG   bitSet  (PORTD,bAvG); bitClear(PORTD,bRecG)
#define   RecG  bitClear(PORTD,bAvG); bitSet  (PORTD,bRecG)
#define   StopG bitClear(PORTD,bAvG); bitClear(PORTD,bRecG)

int pos=0 ;  // global

void SetupEnco() {  
  DDRD |=  0b11110000 ;   // Mettre PD7, 6, 5, 4 en sortie (LEDs des moteurs)
  DDRD &=  0b11110011 ;   // Mettre PD3 et PD2 en entrée (encodeurs)
}

enum {e0,e1,e2,e3}; byte next = e0;

////volatile int pos=0 ;
void DoEnco () {
 switch(next) {
  case e0: 
S1On;
    if (P1On) {pos++; next = e1; }
    if (P2On) {pos--; next = e3; }
S1Off;
    break;
  case e1: 
    if (P2On)  {pos++; next = e2; }
    if (!P1On) {pos--; next = e0; }
    break;
  case e2: 
    if (!P1On) {pos++; next = e3; }
    if (!P2On) {pos--; next = e1; }
    break;
  case e3:
    if (!P2On) {pos++; next = e0; }
    if (P1On)  {pos--; next = e2; }
    break; 
  }
}
