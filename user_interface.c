#include "One_for_all_header.h"


uint8_t key=0;
uint8_t check_key;
Application_State currentState = STATE_HOME_PAGE;
uint8_t  show_data = 0;
uint8_t force_exit = 0;


/*The home page with main menu for the user interface*/
void home_page(void){
  clear_display_text();
//  clear_display_graphic();
  data_2_display(0x30);
  data_2_display(0x00); 
  command_2_display(0x24);
  print_string("***SMART_HOME_PROJECT***");
  
  data_2_display(0x78);
  data_2_display(0x00);
  command_2_display(0x24);
  print_string("Main Menu");
  
  data_2_display(0xA0);
  data_2_display(0x00);
  command_2_display(0x24);
  print_string("1. Temperature");
  
  data_2_display(0xC8);
  data_2_display(0x00);
  command_2_display(0x24);
  print_string("2. Shading system");
  
  data_2_display(0xF0);
  data_2_display(0x00);
  command_2_display(0x24);
  print_string("3. Configure Date and Time");
  
  data_2_display(0x18);
  data_2_display(0x01);
  command_2_display(0x24);
  print_string("4. Current system settings");
}


///*To be able to navigate within the userinterface pages*/
void page_control(void){
  
  key = keypad_value();
  check_key = 0;
  
   if (key == 12/*#*/ || force_exit == 1) {
      currentState = STATE_HOME_PAGE;
      show_data = 0;
    }
  
  if(check_key != key || force_exit == 1){
    force_exit = 0;
    check_key = key;
    switch (currentState) {
        case STATE_HOME_PAGE:
            home_page();
            switch (key) {
                case 1:
                    currentState = STATE_TEMPERATURE_PAGE;
                    break;
                case 2:
                    currentState = STATE_SHADING_SYSTEM_PAGE;
                    break;
                case 3:
                    currentState = STATE_CALENDAR_PAGE;
                    break;
                case 4:
                    currentState = STATE_SETTINGS_PAGE;
            }
            break;

        case STATE_TEMPERATURE_PAGE:
            clear_display_text();
            temp_page();
            
            switch (key){
                case 1:
                    clear_display_text();
                    temp_page();
                    break;
                case 2:
                    clear_display_text();
                    fastmode_switch_display();
                    break;
                case 3:
                    clear_display_text();
                    show_data = 1;
                    temperature_linkedList_2_display();
                    
                    break;
                case 4:
                    clear_display_text();
                    temperature_warning_alarm = 0;
                    alarm_reset_information();
                    break;
                case 5:
                    clear_display_text();
                    change_temperature_limits_from_display();
                    break;
                case 6:
                    clear_display_text();
                    change_periodic_temperature_N();
                    break;
                case 7:
                    clear_display_text();
                    print_graph();
                    break;
                case 8:
                     clear_specific_area(0x2, 0x58, 40);
                    break;    
            }
            break;
            
        case STATE_SHADING_SYSTEM_PAGE:
            clear_display_text();
            shading_system_info_2_display();
            break;

        case STATE_CALENDAR_PAGE:
            // Handle interactions specific to Config Calendar
            config_calendar_from_display();
            break;
        case STATE_SETTINGS_PAGE:
            //some function to show us the current configes
            clear_display_text();
            show_current_setting();
            break;
          
    }
  }
}


/*For the menu of temperature in the temperature page*/
void temp_page(void){
  print_string_at_position(0x87,0x00,"Temperature");
  print_string_at_position(0xA0,0x00,"2. fast mode");
  print_string_at_position(0xC8,0x00,"3. temperature data");
  print_string_at_position(0xF0,0x00,"4. reset alarm");
  print_string_at_position(0x18,0x01,"5. change temperature limit");
  print_string_at_position(0x40,0x01,"6. change N for temperature recording");
  print_string_at_position(0x68,0x01,"7. graph data");
  print_string_at_position(0x90,0x01,"8. clear warnings");
  print_string_at_position(0xB8,0x01,"#. main page");
  
}