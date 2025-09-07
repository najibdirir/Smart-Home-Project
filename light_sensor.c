#include "One_for_all_header.h"

uint16_t light_sensor_1 = 0;
uint16_t light_sensor_2 = 0;

/*initialize the light sensors*/
void light_sensor_init(void){
  *AT91C_PMC_PCER1 = 1<<5; 
  *AT91C_PMC_PCER = 1<<11; 
  *AT91C_PIOA_PER =  (1<<3) | (1<<4);
  *AT91C_PIOA_PPUDR =  (1<<3) | (1<<4); 
  *AT91C_ADCC_MR = (*AT91C_ADCC_MR & 0xFFFF00FF)| 0x200;
}

/*Measure the light sensors using channel 1 and 2 and store them in 2 variables */
void measure_light(void){
  *AT91C_ADCC_CHER = (1<<2) | (1<<1); 
  *AT91C_ADCC_CR = 1<<1; 
  uint8_t data_read = *AT91C_ADCC_CHSR; 
  if((data_read & (1<<2)) == (1<<2))
    light_sensor_1 = (*AT91C_ADCC_CDR2) & (0xFFF); 
  if((data_read & (1<<1)) == (1<<1))
    light_sensor_2 = ((*AT91C_ADCC_CDR1) & (0xFFF)); 
}

