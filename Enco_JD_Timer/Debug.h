// Debug.h 
 int highLow;
 byte flagS1; 
 
#define S1On bitSet (PORTB,0)
#define S1Off bitClear (PORTB,0)
#define S2On bitSet (PORTB,1)
#define S2Off bitClear (PORTB,1)
#define S1S2Out bitSet (DDRB,0); bitSet (DDRB,1)

#define bDa 5 // PORTB pin 13  
#define DaOn   bitClear (PORTB,bDa)
#define DaOff  bitSet  (PORTB,bDa)
#define DaOut  bitSet   (DDRB,bDa)
#define DaIn   (PORTB & (1<<bDa))  // faut pas lire la pin

void SetupDebug() {  // initialisation
  DaOut;  S1S2Out;
}

#define Nbits 16  
enum {AtS1,DebS1,StartS1,BitS1,ContS1,StopS1} eS1 = AtS1; 

  volatile unsigned int hL;
  volatile byte cc, etatLed; 
  
  
void SendS1 () {   // appel toutes les 58 us
  switch (eS1) {
    case AtS1:  // on attend le flag de départ  
      if (flagS1) {  hL=highLow;  eS1 = DebS1;}
      break;
   case DebS1: // on sauv LED, pin 13 à 1
      if (!DaIn) {etatLed=0; DaOff; }  else {etatLed=1;}
      cc=Nbits;  eS1 = StartS1;
      break;
   case StartS1:  //envoie bit
      DaOn; eS1=BitS1;
      break; 
   case BitS1: // coupe si bit=0
     if (!(hL&0x8000)) DaOff;
     eS1 = ContS1; 
     break; 
   case ContS1:
      DaOff; hL <<=1;
      if (cc--) { eS1 = StartS1; }
      else  { eS1 = StopS1; }
      break;
    case StopS1:  
      if (!etatLed) { DaOn; }
      flagS1=0; eS1 = AtS1;
      break;
  } // end switch
}


