#include "One_for_all_header.h"

uint32_t sysTick_counter = 0;
uint8_t light_flag_servo = 0;



uint8_t temp_read = 0;
uint8_t time_read = 0;

uint16_t fast_mode_count =0;


void SysTick_Handler(void){
    sysTick_counter++;
    
    fast_mode_count++;
    if(temperature_measure_flag){
      temperature_measure_delay++;
    }
    if(temperature_measure_delay==16){
      temperature_measure_flag=0;
      temperature_measure_delay=0;
    }
    if(sysTick_counter % 500 == 0){
      temp_read =1;
    }
    if(sysTick_counter % 1000 == 0){
     time_read =1;
     light_flag_servo =1;
     sec_counter++;
    }
    
     light_2_servo(); 
    //time counter, update the clock
    date_time_init();
}


/*To start the sysTIck*/
void init_sysTick(void){
  SysTick_Config((SystemCoreClock/1000)-1);
}

/*TO make a delay*/
void delay(int value){
  int i;
  for(i=0; i<value; i++)
    asm("nop");
}
