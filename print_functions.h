extern uint8_t x;
void print_char(char key);
void print_string(char string[]);
void print_string_at_position(uint8_t data_1, uint8_t data_2, char string[]);
void write_keypad_to_Display(uint8_t key);
extern uint16_t cursor_index_counter;
void print_float_2_display(float digit);
void print_int_2_display(uint16_t digit);
void print_time_and_date_2_display(void);
void print_current_temperature_2_display(float temp);
void temperature_linkedList_2_display(void);
void shading_system_info_2_display(void);
void alarm_reset_information(void);
void change_temperature_limits_from_display(void);
void change_periodic_temperature_N(void);
void fastmode_switch_display(void);
void show_current_setting(void);
void cool_display(void);
void print_graph(void);
void make_days(void);




