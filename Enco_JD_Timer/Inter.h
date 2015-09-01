// Inter.h tous les inter

volatile byte cnt,cnte;
ISR (TIMER2_OVF_vect) {
 TCNT2 = 141;  //  58 us calibre avec corr
 DoEnco();
    PORTC = pos;
 SendS1(); 
 if (cnte++ > 50) { // toutes les 50x58= 2.5ms 
   cnte=0;
 //  DoEnco();
 }
 if (cnt++ > 250) { // toutes les 250x58= 20ms 
   cnt=0;
   highLow = pos;
   flagS1 = 1;
//   PORTC = pos;
 }
} 

void SetupInter() {  // initialisation
  TCCR2A = 0; //default
  TCCR2B = 0b00000010;  // clk/8
  TIMSK2 = 0b00000001;  // TOIE2
  sei();
}



