
#include "One_for_all_header.h"

int main()
{
  SystemInit();
  init_sysTick();
  hardware_init();
  cool_display();
  clear_display_text();
  clear_display_graphic(); 
  change_calendar(11,1,24,12,20,0);
  home_page();
  void show_temp(void);
  
  while(1){
    
    show_temp();
    
    //varje minut record
    N_recording();
    
    //fast mode på n_recoding
    record_N_temp_fast_mode();
    
    page_control();
    
  }
  return 0;
}
void show_temp(void){
  if(temp_read){
      temp_read =0;
      read_temperature_value();  
      print_current_temperature_2_display(temperature_current_value);       
    }  
}