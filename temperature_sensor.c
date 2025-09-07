#include "One_for_all_header.h"

float temperature_current_value = 0;
/*values according to the assignement*/
uint8_t lower_temperature_limit = 20;
uint8_t upper_temperature_limit = 25;
uint8_t temperature_warning_alarm = 0;
uint8_t temperature_measure_flag;
uint8_t temperature_measure_delay;


/*This will initialize the temperature sensor*/
void temperature_init(void){
  temperature_measure_flag = 1;
  *AT91C_PMC_PCER = (1<<12); 
  *AT91C_PMC_PCER = (1<<27); 
  *AT91C_TC0_CCR = 0x5;
  *AT91C_TC0_CMR = (*AT91C_TC0_CMR & 0xFFFFFFF8)|(1<<18) | (1<<17); 
  *AT91C_PIOB_PER = (1<<25);  
  *AT91C_PIOB_PPUDR = (1<<25); 
  *AT91C_PIOB_OER = (1<<25);
  *AT91C_PIOB_SODR = (1<<25);
  *AT91C_PIOB_CODR = (1<<25);
  //wait for some systick interrupt 16ms
  while(temperature_measure_flag == 1){} 
  *AT91C_PIOB_SODR = (1<<25);
  NVIC_ClearPendingIRQ(TC0_IRQn); 
  NVIC_SetPriority(TC0_IRQn, 1);
  NVIC_EnableIRQ(TC0_IRQn);
  *AT91C_TC0_IER = (1<<6); 
  start_temperature_puls();
}

/*This will create a pulse for measuring temperature*/
void start_temperature_puls(void){
  temperature_measure_flag = 1;
  *AT91C_PIOB_OER = (1<<25);
  *AT91C_PIOB_SODR= (1<<25); 
  *AT91C_PIOB_CODR = (1<<25);
  //wait for some systick interrupt 16ms
  while(temperature_measure_flag){} 
  *AT91C_PIOB_SODR = 1<<25; 
  *AT91C_PIOB_CODR= 1<<25; 
  delay(25);
  *AT91C_PIOB_SODR= 1<<25; 
  *AT91C_PIOB_ODR = 1<<25; 
  *AT91C_TC0_SR;
  *AT91C_TC0_CCR = 0x4; 
  *AT91C_TC0_IER = 1<<6;  
}

//TC0 interrupt handler
void TC0_Handler(){
  *AT91C_TC0_IDR = (1<<6);
  temperature_measure_flag = 1;
}

/*To read the value from the temp sensor*/
void read_temperature_value(void){
    uint32_t rB = *AT91C_TC0_RB;
    uint32_t rA = *AT91C_TC0_RA;
    start_temperature_puls();
    temperature_current_value = ((float)(rB-rA)/210)-273.15;
    check_temperature_limit(); //kolla up det
}

/*This will check if the temperature limits have been breached*/
void check_temperature_limit(void){
  if((upper_temperature_limit < temperature_current_value) || (lower_temperature_limit > temperature_current_value)){
    //vi s tter larmet genom att t nda lampan
    temperature_warning_alarm = 1;
    set_red_led(1);
    set_green_led(0);
  }
  else if(temperature_warning_alarm == 0){
  set_green_led(1);
  set_red_led(0);
  }
}


/*For teh WARNING on LCD, THese LEDS are used*/

void Led_init(void){
   //enable PIOD using PMC_PCER0
  *AT91C_PMC_PCER = (1<<14);
  //enable PIOA in PMC
  *AT91C_PMC_PCER = (1<<11);
  //enable GPIO line for 23 and 24
  *AT91C_PIOA_PER = (0x3<<14);
   //diable pullup resistor for 14 and 15
  *AT91C_PIOA_PPUDR = (0x3<<14);
   //assign the pin for 14 and 15
  *AT91C_PIOA_OER = (0x3<<14);
}


void set_red_led(uint8_t key){
  if(key){
    *AT91C_PIOA_SODR = (1<<14);
  }
  else{
    *AT91C_PIOA_CODR = (1<<14);
  }
  
}


void set_green_led(uint8_t key){
  
  if(key){
    *AT91C_PIOA_SODR = (1<<15);
  }
  else{
    *AT91C_PIOA_CODR = (1<<15);
  }
}