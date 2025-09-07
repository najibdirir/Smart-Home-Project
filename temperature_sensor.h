
extern float temperature_current_value;
extern uint8_t lower_temperature_limit;
extern uint8_t upper_temperature_limit;
extern uint8_t temperature_warning_alarm;
void temperature_init(void);
void start_temperature_puls(void);
void TC0_Handler();
void read_temperature_value(void);
void check_temperature_limit(void);


// for the leds that will be used for warning

void Led_init(void);
void set_red_led(uint8_t key);
void set_green_led(uint8_t key);




