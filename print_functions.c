#include "One_for_all_header.h"

uint16_t cursor_index_counter = 0;
uint8_t x =0;
temp_data_day days[7]; // kolla up det
uint8_t fast_mode_flag = 0;

/*Print just one char*/
void print_char(char key){
  data_2_display(key-0x20);
  command_2_display(0xC0);
}

/*This will print characters or string*/
void print_string(char string[]){
  uint8_t n =0;
  while(string[n] != '\0'){                             
    print_char(string[n]);
    n++;
  }
}

/*This will print a string at given address on the LCD*/
void print_string_at_position(uint8_t data_1, uint8_t data_2, char string[]){
  set_pointer_at(data_2, data_1);
  print_string(string);
}

/*write directly to display from keypad*/
void write_keypad_to_Display(uint8_t key){
  if((cursor_index_counter > 0) & (cursor_index_counter%(600) == 0)){
    clear_display_text();
  }
  if(key != 0){
    unsigned char value = 0x10;
    value = value + (unsigned char) key;
    if(value == 0x1A){ value = 0xA;}; // print * when data is 10
    if(value == 0x1B){ value = 0x10;}; // print 0 when data 11;
    if(value == 0x1C){ value = 0x3;}; //print # when data is 12;
      
    data_2_display(value);
    command_2_display(0xC0);
    cursor_index_counter++;
    delay(2000000);
  }  
}

/*This will print a number with decimal to display*/
void print_float_2_display(float digit){
  char nums[16];
  sprintf(nums, "%2.1f", digit);
  print_string(nums);
}

/*This will print a number to the LCD*/
void print_int_2_display(uint16_t digit){
  char nums[16];
  sprintf(nums, "%d", digit);
  print_string(nums);
}

/*This will print date and time at the top of LCD*/
void print_time_and_date_2_display(void){
  data_2_display(0x00);
  data_2_display(0x00);
  command_2_display(0x24);
  print_time_and_date(current_time_date);  
}

/*This will print the temperature to LCD on top corner*/
void print_current_temperature_2_display(float temp){
  data_2_display(0x22);//22
  data_2_display(0x00);//0
  command_2_display(0x24);
  print_float_2_display(temp);
  if(x == 0){
    data_2_display(0x07);
    command_2_display(0xC0);
    
    data_2_display(0x23);
    command_2_display(0xC0); 
  }
  x = 1;
}

/*For the user interface, information on the temperature data that is to be printed*/
void temperature_linkedList_2_display(void){
  clear_display_text();
  print_string_at_position(0x90,0x01," Temperature data:");

  print_string_at_position(0x30,0x02,"#. Exit to main page");
  if(fast_mode_flag == 1){
    print_string_at_position(0xA4,0x01," every second. ");
    print_string_at_position(0xE8,0x01," Sampling number: ");
    print_int_2_display(N);
    
  }
  if(fast_mode_flag == 0){
    print_string_at_position(0xA4,0x01," every minute.");
    print_string_at_position(0xE8,0x01," Sampling number: ");
    print_int_2_display(N);
  }
  key=0;
  if(key != 12){
    key = keypad_value();
    
  }
}

/*This will come up in the user interface, information*/
void shading_system_info_2_display(void){
  clear_display_text();
  print_string_at_position(0x78,0x00,"1. Disable shading system");
  print_string_at_position(0xc8,0x00,"2. Enable shading system");
  print_string_at_position(0x40,0x01,"#. Main page");
  while((key = keypad_value())){
    switch (key){
      case 1:
        servo_activator = 0;
        clear_specific_area(0x2, 0x6C, 20);
        print_string_at_position(0x74,0x02,"Disabled!");
        delay(30000000);
        clear_specific_area(0x2, 0x6C, 20);
        break;
      case 2:
        servo_activator = 2;
        clear_specific_area(0x2, 0x6C, 20);
        print_string_at_position(0x74,0x02,"Enabled!  ");
        delay(30000000);
        clear_specific_area(0x2, 0x6C, 20);
        break;
    }
  }
}

/*This will show up in the user interface when alarm is reseted*/
void alarm_reset_information(void){
  print_string_at_position(0x6C,0x02,"Alarm reseted.!");
  delay(10000000);
  clear_specific_area(0x2, 0x58, 40);
  force_exit = 1;
}

/*This will change the limit from display by the user*/
void change_temperature_limits_from_display(void){
 print_string_at_position(0x78,0x00,"Lower limit: ");
 print_int_2_display(lower_temperature_limit);
 print_string_at_position(0xC8,0x00,"Upper limit: ");
 print_int_2_display(upper_temperature_limit);
 print_string_at_position(0x18,0x1,"write '^'-> to alter");
 print_string_at_position(0x40,0x1,"(*): right");
 
  clear_specific_area(0x2, 0x08, 10);
  print_string_at_position(0x08,0x02,"#. OK");
  
  key=0;
  cursor_index_counter = 0;
  while(key != 12/*#*/){
    set_pointer_at(0x0, 0xAD+cursor_index_counter); //below the calander
    print_char('^');
    key = keypad_value();
    delay(3000000);
      if(key == 10 && cursor_index_counter < 81){
        set_pointer_at(0,0xAD+cursor_index_counter);
        print_char(' ');
        if(cursor_index_counter ==1){
          cursor_index_counter +=79;
        }else{
          cursor_index_counter ++;
        }
        set_pointer_at(0,0xAD+cursor_index_counter);
        print_char('^');
      }
    
      if(key!=0 && key != 10 && key != 12){
        if(key == 11)
          key = 0;
        switch(cursor_index_counter){
          case 0:
            lower_temperature_limit =0;
            lower_temperature_limit = key * 10 + lower_temperature_limit % 10;
            if(lower_temperature_limit > upper_temperature_limit){
              lower_temperature_limit = upper_temperature_limit;
            }
          break;
          case 1:
            lower_temperature_limit = lower_temperature_limit - lower_temperature_limit % 10 + key; 
            if(lower_temperature_limit > upper_temperature_limit){
              lower_temperature_limit = upper_temperature_limit;
            }
          break; 
          case 80:
            upper_temperature_limit =0;
            upper_temperature_limit = key * 10 + upper_temperature_limit % 10;
            if(upper_temperature_limit < lower_temperature_limit){
              upper_temperature_limit = lower_temperature_limit;
            }
          break;
          case 81:
            upper_temperature_limit = upper_temperature_limit - upper_temperature_limit % 10 + key; 
            if(upper_temperature_limit < lower_temperature_limit){
              upper_temperature_limit = lower_temperature_limit;
            }
          break; 
        }//switch -end-
        set_pointer_at(0x00, 0x85);
        print_int_2_display(lower_temperature_limit);
        set_pointer_at(0x00,0xD5);
        print_int_2_display(upper_temperature_limit);
      }//if statement -end-
  }//while -end-
  clear_specific_area(0x2, 0x08, 20);
  print_string_at_position(0x08,0x02,"#. main page");
}


/*THis is to change the N sampling number from display*/
void change_periodic_temperature_N(void){
  print_string_at_position(0x50,0x00, "Periodic temperature recording N minute");
  print_string_at_position(0x78,0x00,"N: ");
  print_int_2_display(N);
  print_string_at_position(0x18,0x1,"press[0-9], 0 = 10");
  print_string_at_position(0x68,0x01,"#. go back");
  
  key=0;
  while(key != 12/*#*/){
    delay(3000000);
    key = keypad_value();
    
      if(key !=0  && key != 10 && key != 12){
        clear_specific_area(0x00,0x7B, 2);
        if(key == 11)
          key = 10;
        N = key;
        set_pointer_at(0x00, 0x7B);
        print_int_2_display(N);
      }//if statement -end-
  }//while -end-
}


/*For the user interface when fast mode is activated or deactivated*/
void fastmode_switch_display(void){
  print_string_at_position(0x78,0x00,"1. Enable fastmode");
  print_string_at_position(0xc8,0x00,"2. Disable fastmode");
  print_string_at_position(0x40,0x01,"#. main page");
  key=0;
  while(key!=12){
    key = keypad_value();
    switch (key){
      case 1:
        fast_mode_flag = 1;
        clear_specific_area(0x2, 0x6C, 20);
        print_string_at_position(0x6C,0x02,"Fastmode enabled!");
        delay(10000000);
        clear_specific_area(0x2, 0x58, 40);
        break;
      case 2:
        fast_mode_flag = 0;
        clear_specific_area(0x2, 0x6C, 20);
        print_string_at_position(0x6C,0x02,"Fastmode disabled! ");
        delay(10000000);
        clear_specific_area(0x2, 0x58, 40);
        break;
    }
  }
}

/*To show the current setting of the system*/
void show_current_setting(void){
  print_string_at_position(0x28,0x00,"---These are the current settings---");
  print_string_at_position(0x50,0x00,"Sampling(N) number: ");
  print_int_2_display(N);
  if(fast_mode_flag ==1)
    print_string_at_position(0xA0,0x00,"Fast mode: Active");
  if(fast_mode_flag ==0)
    print_string_at_position(0xA0,0x00,"Fast mode: Inactive");
  if(servo_activator ==2)
    print_string_at_position(0xF0,0x00,"Shading system: Active");
  if(servo_activator ==0)
    print_string_at_position(0xF0,0x00,"Shading system: Inactive");
  
  print_string_at_position(0x40,0x01,"Temperature lower limit: ");
  print_float_2_display(lower_temperature_limit);
  print_string_at_position(0x90,0x01,"Temperature upper limit: ");
  print_float_2_display(upper_temperature_limit);
  print_string_at_position(0x30,0x02,"#. Main menu");
  print_string_at_position(0xE0,0x01,"Calendar: ");
  while(key != 12){
    key = keypad_value();
    set_pointer_at(0x01, 0xEB);
    print_time_and_date(current_time_date);
  }
}

/*LCD Intro*/
void cool_display(void){
    for(int i=15; i>0; i--){
    draw_line(i,15-i, 0xDE, 120-(i*8));
    delay(1000000);
  }
  for(int i=39; i>24; i--){
    draw_line(i-24,i, 0xDE, 120-((i-24)*8));
    delay(1000000);
  } 
  for(int i=0; i<10; i++){
    draw_line(8,i+15, 0xFF, 56);
    delay(1000000);
  }
  print_string_at_position(0x39, 0x00, "Smart");
  delay(10000000);
  print_string_at_position(0x61, 0x00, "Home");
  delay(10000000);
  print_string_at_position(0x89, 0x00, "Project");
  delay(10000000);
  print_string_at_position(0xB1, 0x00, "Gr-27");
    for(int i=0; i<10; i++){
    draw_line(8,i+15, 0x11, 56);
    delay(1000000);
  }
    for(int i=0; i<10; i++){
    draw_line(8,i+15, 0xFF, 56);
    delay(1000000);
  }
      for(int i=0; i<10; i++){
    draw_line(8,i+15, 0xB, 56);
    delay(1000000);
  }
      for(int i=0; i<10; i++){
    draw_line(8,i+15, 0xFF, 56);
    delay(1000000);
  }
  delay(30000000);
}


/*For printing graph*/
void print_graph(void){ 
  print_string_at_position(0x2B, 0x0, "(#) main menu");
  print_string_at_position(0x04, 0x0, "temp are in order of (max, avg, min)"); 
  make_days();
    // row_pos, col_pos, data,amount
  draw_line(1,2, 0x01, 13*8);
  for(int i=3; i<39; i++)
    draw_line(14,i, 0xFF, 1); 
    print_string_at_position(0x29, 0x00, "C");    
    print_string_at_position(0x50, 0x00, "30");    
    print_string_at_position(0x78, 0x00, "29");    
    print_string_at_position(0xa0, 0x00, "28");    
    print_string_at_position(0xc8, 0x00, "27"); 
    print_string_at_position(0xf0, 0x00, "26");
    print_string_at_position(0x18, 0x01, "25");
    print_string_at_position(0x40, 0x01, "24");
    print_string_at_position(0x68, 0x01, "23");
    print_string_at_position(0x90, 0x01, "22");
    print_string_at_position(0xb8, 0x01, "21");
    print_string_at_position(0xe0, 0x01, "20");
    print_string_at_position(0x08, 0x02, "19");
    
    for(int i=3; i<39; i++){
      for(int j=3; j<14; j++)
        draw_line(j,i, 0x1, 1);
    }   
    
    print_string_at_position(0x5B,0x2, "|D-1|");
    print_string_at_position(0x60,0x2, "|D-2|");
    print_string_at_position(0x65,0x2, "|D-3|");
    print_string_at_position(0x6A,0x2, "|D-4|");
    print_string_at_position(0x6F,0x2, "|D-5|");
    print_string_at_position(0x74,0x2, "|D-6|");
    print_string_at_position(0x79,0x2, "|D-7|");
    
    for(uint8_t i = 0; i<7; i++){
      uint8_t temp = 33-(days[i].max_temp->temperaturData);
      uint8_t temp1 = 33-(days[i].min_temp->temperaturData);
      uint8_t avg = 33-(days[i].avg_temp);

      draw_line(temp, 4+(5*i),0xDE, 112-(8*temp));
      draw_line(avg, 4+(5*i+1),0xDE, 112-(8*avg));
      draw_line(temp1, 4+(5*i+2),0xDE, 112-(8*temp1));
    }
    while(key != 12)
      key = keypad_value();
    
   clear_display_graphic();
   clear_specific_area(0x2, 0x58, 40);
   clear_display_text();
   force_exit = 1;
}
void make_days(void){
  uint8_t i= 0;
  uint8_t x = 24;
  while(i < 7){
     x += i;
     linkedList_node* max = createNode(current_time_date, x);
     linkedList_node* min = createNode(current_time_date, x-3);
  
     days[i].avg_temp = (x+(x-3))/2;
     days[i].max_temp = max;
     days[i].min_temp = min;
     i++;
     x = 24;
  }

}
