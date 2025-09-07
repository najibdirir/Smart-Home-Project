
//time and date struct for the purpose of timestamp and calendar
typedef struct time_date {
  uint8_t day:5; 
  uint8_t month:4; 
  uint8_t year; 
  uint8_t hour:5; 
  uint8_t minute:6; 
  uint8_t second:6; 
} time_date;
//this will be our main time and date counter
extern time_date current_time_date;
void print_time_and_date(time_date calendar);
void date_time_init(void);
extern uint8_t record_minute_linkedList;
extern uint8_t record_sec_linkedList;
void addCalendar(const time_date *new_kalendar);
extern uint8_t cursor_check;
void config_calendar_from_display(void);
void change_calendar(uint8_t day, uint8_t month, uint8_t year, uint8_t hour, uint8_t min, uint8_t sec);






