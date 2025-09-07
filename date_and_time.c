#include "One_for_all_header.h"

#define BASE_YEAR 2000
time_date current_time_date;
uint8_t record_sec_linkedList = 0;
uint8_t record_minute_linkedList = 0;
uint8_t cursor_check = 0;
uint8_t day = 0, month = 0, year = 0, hour = 0, min = 0, sec = 0;

// this will print time and date to display
  // printa time_date p  sk rmen och anv nd sprinf()
void print_time_and_date(time_date calendar) {
    char formattedDate[11]; // DD/MM/YYYY + '\0'
    char formattedTime[9];  // hh:mm:ss + '\0' 
    uint16_t fullYear = calendar.year + BASE_YEAR;
    sprintf(formattedDate, "%02hhu/%02hhu/%04u", calendar.day, calendar.month, fullYear);
    sprintf(formattedTime, "%02hhu:%02hhu:%02hhu", calendar.hour, calendar.minute, calendar.second);
    print_string(formattedDate);
    data_2_display(0x00); //Character 'Space'
    command_2_display(0xC0);
    print_string(formattedTime);
}

/*To count the time and date the system use*/
void date_time_init(void){
  if(time_read ==1){
    time_read =0;
    current_time_date.second ++;
    record_sec_linkedList = 1;
      if(current_time_date.second % 60 == 0){
        current_time_date.minute++;
        record_minute_linkedList = 1;
        current_time_date.second = 0;
        if(current_time_date.minute % 60 == 0){
          current_time_date.hour++;
          current_time_date.minute =0;
          if(current_time_date.hour % 24 == 0){
            current_time_date.hour =0;
            current_time_date.day++;
            if(current_time_date.day % 30 ==0){
                current_time_date.month++;
                current_time_date.day = 0;
                if(current_time_date.month % 12 ==0){
                    current_time_date.year++;
                    current_time_date.month =0;
                    }
                }
            }
        }
      }
  }
}

/*To add a time and date*/
void addCalendar(const time_date *new_kalendar){
  //impelemtera kod genom att l ta anv ndaren konfig kalender
  current_time_date.day = new_kalendar->day;
  current_time_date.month = new_kalendar->month;
  current_time_date.year = new_kalendar->year;
  current_time_date.second = new_kalendar->second;
  current_time_date.minute = new_kalendar->minute;
  current_time_date.hour = new_kalendar->hour;
}


/*To change the time and date from display*/
void config_calendar_from_display(void){
  clear_display_text();
  delay(5000000); 
  print_string_at_position(0x78,0x0,"Alter->: ");
  print_time_and_date(current_time_date);
  print_string_at_position(0x18,0x01,"move '^'-> to alter");
  print_string_at_position(0x68,0x01,"(*): right");
  clear_specific_area(0x2, 0x08, 20);
  print_string_at_position(0x08,0x02,"(#): OK");
  //---------------------------------
  key=0;
  while(key != 12 /*#*/){
    set_pointer_at(0x0, 0xa9+cursor_check); //below the calander
    print_char('^');
    key = keypad_value();
    delay(3000000);
    if(cursor_check <= 18){
      if(key == 10){
        set_pointer_at(0,0xa9+cursor_check);
        print_char(' ');
        if(cursor_check < 18)
          if(cursor_check == 1 || cursor_check==4 || cursor_check==9 || cursor_check == 12 || cursor_check ==15){
            if(cursor_check == 4){
              cursor_check +=4;
            }else{
              cursor_check +=2;
            }
          }else{
          cursor_check++;
          }
        set_pointer_at(0,0xa9+cursor_check);
        print_char('^');
      }
      if(key && key != 10 && key != 12){
        if(key == 11) // it means 0
          key=0;
        switch(cursor_check){
        case 0:
          day = key * 10 + day % 10;
          if(day > 30){
            current_time_date.day = 30;
          }else{
            current_time_date.day = day;
          }
            break;                                                     
        case 1:
          day = day - day % 10 + key; 
          if(day > 30){
            current_time_date.day = 30;
          }else{
            current_time_date.day = day;
          }
          break; 
       //-------------------------------
        case 3:
          month = key * 10 + month % 10; 
          if(month > 12){
            current_time_date.month = 12;
          }else{
            current_time_date.month = month;
          }
          break;
        case 4:
          month = month - month % 10 + key; 
          if(month > 12){
            current_time_date.month = 12;
          }else{
            current_time_date.month = month;
          }
          break; 
         //------------------------------ 
        case 8:
          year = key * 10 + year % 10; 
          if(year > 99){
            current_time_date.year = 99;
          }else{
            current_time_date.year = year;
          }
          break;
        case 9:
          year = year - year % 10 + key;  
          if(year > 99){
            current_time_date.year = 99;
          }else{
            current_time_date.year = year;
          }
          break;
       //--------------------------------
        case 11:
          hour = key * 10 + hour % 10; 
          if(hour > 24){
            current_time_date.hour = 24;
          }else{
            current_time_date.hour = hour;
          }
          break;
        case 12:
          hour = hour - hour % 10 + key;  
          if(hour > 24){
            current_time_date.hour = 24;
          }else{
            current_time_date.hour = hour;
          }
          break;
          //------------------------------
        case 14:
          min = key * 10 + min % 10; 
          if(min > 60){
            current_time_date.minute = 60;
          }else{
            current_time_date.minute = min;
          }
          break;
        case 15:
          min = min - min % 10 + key;  
          if(min > 60){
            current_time_date.minute = 60;
          }else{
            current_time_date.minute = min;
          }
          break;
          //------------------------------
        case 17:
          sec = key * 10 + sec % 10; 
          if(sec > 60){
            current_time_date.second = 60;
          }else{
            current_time_date.second = sec;
          }
          break;
        case 18:
          sec = sec - sec % 10 + key; 
          if(sec > 60){
            current_time_date.second = 60;
          }else{
            current_time_date.second = sec;
          }
          break;
        }
        set_pointer_at(0,0x81);
        print_time_and_date(current_time_date);
      }
    }
  }//end of while loop 
  cursor_check = 0;
  clear_specific_area(0x2, 0x08, 20);
  print_string_at_position(0x08,0x02,"(#): Main page");
}


/*To change the time and date with arguments*/
void change_calendar(uint8_t day, uint8_t month, uint8_t year, uint8_t hour, uint8_t min, uint8_t sec){
  current_time_date.day = day;
  current_time_date.month = month;
  current_time_date.year = year;
  current_time_date.second = sec;
  current_time_date.minute = min;
  current_time_date.hour = hour;
}