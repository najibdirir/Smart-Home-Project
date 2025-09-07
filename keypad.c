#include "One_for_all_header.h"

#define ROWS 4
#define COLUMNS 3

/*Initialize the pins for the keypad hardware*/
void keypad_init(void){
  *AT91C_PMC_PCER = (3<<13);
  *AT91C_PIOC_PER = 0x3BC;
  *AT91C_PIOD_PER = (1<<2);
  *AT91C_PIOD_PPUDR = (1<<2);
  *AT91C_PIOC_PPUDR = 0x3BC; 
  *AT91C_PIOD_OER = (1<<2);
  *AT91C_PIOD_SODR = (1<<2);
  *AT91C_PIOC_ODR = 0x3C;
}

/*THis will read the value from keypad when pressed*/
uint8_t keypad_value(void){
  uint8_t value = 0;
  *AT91C_PIOD_CODR = (1<<2);
  *AT91C_PIOC_OER = (0x380); 
  *AT91C_PIOC_SODR = (0x380);
  for(uint8_t i = 0; i<COLUMNS; i++){
    *AT91C_PIOC_CODR = (1 << (i + 7));
    for(uint8_t j=0; j<ROWS; j++){
      if (!(*AT91C_PIOC_PDSR & (1 << (j + 2)))) { 
                value = (j * COLUMNS) + i + 1;                 
            }
    }
    *AT91C_PIOC_SODR = (1 << (i + 7));    
  }
  *AT91C_PIOC_ODR = (0x380);
  return value;
}