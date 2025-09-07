#include "One_for_all_header.h"

#define MAX_NODES 341
uint8_t N = 4;
uint8_t N_checker = 0;
uint8_t sec_counter = 0; 
uint16_t display_position_for_print = 0x51;
float tota_temp = 0;
float medel_temp = 0;
uint8_t first_char = 0;
linkedList_node *temp_N_recordings = NULL;
linkedList_node* minsta_temperature = NULL;
linkedList_node* maximum_temperature = NULL;
temp_data_day temp_days = NULL;
uint8_t index_display = 0;
uint8_t my_day = 1;
linkedList_node *temp_node = NULL;
uint16_t divider;
uint16_t mode_counter;
int lastSampleTime = 0;
//i have a likedList with its average, low and high 
void N_recording(void){
  if(fast_mode_flag == 0 && show_data == 1){
    if(N_checker == 0){
      N_checker = N;
      lastSampleTime = -1;
    }
  uint8_t samplingInterval = (N > 0) ? (60 / N) : 60;
  if((sec_counter % samplingInterval == 0) && (sec_counter != lastSampleTime) && (sec_counter !=0) && (N_checker != 0)){
    lastSampleTime = sec_counter;
    temp_node = NULL;
    temp_node = createNode(current_time_date, temperature_current_value);
    tota_temp += temp_node->temperaturData;
    if(maximum_temperature == NULL || maximum_temperature->temperaturData < temp_node->temperaturData){
      if(maximum_temperature != NULL){
        free(maximum_temperature);
      }
      maximum_temperature = createNode(current_time_date, temp_node->temperaturData);
    }
    
    if(minsta_temperature == NULL || minsta_temperature->temperaturData > temp_node->temperaturData){
      if(minsta_temperature != NULL){
        free(minsta_temperature);
      }
      minsta_temperature = createNode(current_time_date, temp_node->temperaturData);
    }
    
    free(temp_node);
    //decrement so we can do N times measurement per min
    N_checker--;  
    
  }
  if(N_checker == 0){
    //MAX-NODES has to be checked, for the capacity???
    if(linkedList_node_counter >= 341){
      remove_last_LinkedList_node(&temp_N_recordings);
      print_string_at_position(0x62,0x2,"Memory was full!");
    }
    medel_temp = tota_temp/N;
    
    temp_days.avg_temp = medel_temp;
    temp_days.max_temp = maximum_temperature;
    temp_days.min_temp = minsta_temperature;
       if(index_display < 7){
       print_temperature_linkedList_2_display(temp_days, index_display, my_day);
       index_display++;
       my_day++;
       }
    if(index_display == 7){
      index_display = 0;
      }   
    linkedList_node *node_temp = createNode(current_time_date, medel_temp);  
    if(node_temp != NULL){
        insertFirst(&temp_N_recordings, node_temp);
      } 
    maximum_temperature = NULL;
    minsta_temperature = NULL;
    tota_temp = 0;
    medel_temp = 0; 
    free(node_temp);
    N_checker = N; // Reset N_checker for the next cycle
    lastSampleTime = -1; 
  }
  }  
}

//fast mode
void record_N_temp_fast_mode(void) { 
  
  if (fast_mode_flag == 1 && show_data ==1){
      if(N_checker == 0){
    N_checker = N;
    lastSampleTime = sysTick_counter; 
  }
  uint16_t baseInterval = 1000 / N;
  static uint16_t accumulatedError = 0;
  uint16_t actualInterval = baseInterval + accumulatedError;
  accumulatedError = (1000 % N) - accumulatedError;
  if((sysTick_counter - lastSampleTime >= actualInterval) && (N_checker != 0)){
    lastSampleTime = sysTick_counter;
    temp_node = NULL;
    temp_node = createNode(current_time_date, temperature_current_value);
    tota_temp += temp_node->temperaturData;
    if(maximum_temperature == NULL || maximum_temperature->temperaturData < temp_node->temperaturData){
      if(maximum_temperature != NULL){
        free(maximum_temperature);
      }
      maximum_temperature = createNode(current_time_date, temp_node->temperaturData);
    }
    
    if(minsta_temperature == NULL || minsta_temperature->temperaturData > temp_node->temperaturData){
      if(minsta_temperature != NULL){
        free(minsta_temperature);
      }
      minsta_temperature = createNode(current_time_date, temp_node->temperaturData);
    }
    
    free(temp_node);
    //decrement so we can do N times measurement per min
    N_checker--;  
    
  }
  if(N_checker == 0){
    //MAX-NODES has to be checked, for the capacity???
    if(linkedList_node_counter >= 341){
      remove_last_LinkedList_node(&temp_N_recordings);
      print_string_at_position(0x62,0x2,"Memory was full!");
    }
    medel_temp = tota_temp/N;
    
    temp_days.avg_temp = medel_temp;
    temp_days.max_temp = maximum_temperature;
    temp_days.min_temp = minsta_temperature;
       if(index_display < 7){
       print_temperature_linkedList_2_display(temp_days, index_display, my_day);
       index_display++;
       my_day++;
       }
    if(index_display == 7){
      index_display = 0;
      }   
    linkedList_node *node_temp = createNode(current_time_date, medel_temp);  
    if(node_temp != NULL){
        insertFirst(&temp_N_recordings, node_temp);
      } 
    maximum_temperature = NULL;
    minsta_temperature = NULL;
    tota_temp = 0;
    medel_temp = 0; 
    free(node_temp);
    N_checker = N;
  }
  }
}


/*To print the temperature data from linkedList to the LCD*/
void print_temperature_linkedList_2_display(temp_data_day temp_data , uint8_t display_index, uint8_t day){
  print_string_at_position(0x29, 0x00, "Day");
  print_string_at_position(0x2E, 0x00, "MAX_TEMP");
  print_string_at_position(0x3C, 0x00, "MIN_TEMP");
  print_string_at_position(0x49, 0x00, "Average");
  
  display_position_for_print = display_position_for_print+(display_index*0x28);// 1 3 5 7 9 11 13
  row_index_fix(display_position_for_print);
  set_pointer_at(first_char, display_position_for_print); //+40
  clear_specific_area(first_char, display_position_for_print-1, 0x28);
  print_int_2_display(day);
  
  if(display_position_for_print+0x4)
    row_index_fix(display_position_for_print+0x4);
  set_pointer_at(first_char, display_position_for_print+0x4); //+40
  print_int_2_display(temp_data.max_temp->hour);
  print_char(':');
  print_int_2_display(temp_data.max_temp->min);
  print_char(':');
  print_int_2_display(temp_data.max_temp->sec);
  
  if(display_position_for_print+0xD)
    row_index_fix(display_position_for_print+0xD);
  set_pointer_at(first_char, display_position_for_print+0xD);
  print_float_2_display(temp_data.max_temp->temperaturData);
  
  if(display_position_for_print+0x13)
    row_index_fix(display_position_for_print+0x13);
  
  set_pointer_at(first_char, display_position_for_print+0x13); //+40
  print_int_2_display(temp_data.min_temp->hour);
  print_char(':');
  print_int_2_display(temp_data.min_temp->min);
  print_char(':');
  print_int_2_display(temp_data.min_temp->sec);
  
  if(display_position_for_print+0x1C)
    row_index_fix(display_position_for_print+0x1C);
  set_pointer_at(first_char, display_position_for_print+0x1C);
  print_float_2_display(temp_data.min_temp->temperaturData);
  
   if(display_position_for_print+0x22)
    row_index_fix(display_position_for_print+0x22);
  set_pointer_at(first_char, display_position_for_print+0x22); //+40
  print_float_2_display(temp_data.avg_temp);
  first_char = 0;
  display_position_for_print = 0x51;
}
void row_index_fix(uint16_t check){
  if(check > 0xFF && check <0x200){
    first_char = 0x1;
    check = check - 0x100;
  }
  if(check >= 0x200){
    first_char = 0x2;
    check = check - 0x200;
  }
}