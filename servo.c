#include "One_for_all_header.h"

uint8_t servo_activator = 0;

/*Initialize the servo pins*/
void servo_init(void){
  *AT91C_PMC_PCER1 = (1<<4);
  *AT91C_PMC_PCER = (1<<12);
  *AT91C_PIOB_PDR = (1<<17);
  *AT91C_PIOB_ABMR = (1<<17);  
  *AT91C_PWMC_ENA = (1<<1);
  *AT91C_PWMC_CH1_CMR = 0x5; 
  *AT91C_PWMC_CH1_CPRDR = 52499;
  *AT91C_PWMC_CH1_CDTYR = 26250;
  *AT91C_PWMC_CH1_CDTYUPDR =1837;
}

/*To move the servo with degrees as argument, between 0 to 160 degrees*/
void move_servo(uint8_t degree){ 
  *AT91C_PWMC_CH1_CDTYUPDR = 1837+26*degree;
}


void move_servo_from_keypad(uint8_t key){
  switch(key){
    case 1:
      move_servo(10);
      break;
    case 2:
      move_servo(20);
      break;
    case 3:
      move_servo(30);
      break;
    case 4:
      move_servo(40);
      break;
    case 5:
      move_servo(50);
      break;
    case 6:
      move_servo(60);
      break;
    case 7:
      move_servo(70);
      break;
    case 8:
      move_servo(80);
      break;
    case 9:
      move_servo(90);
      break;
    case 11:
      move_servo(0);
      break;
  }   
}