extern uint32_t sysTick_counter;
void SysTick_Handler(void);
extern uint8_t temperature_measure_delay;
extern uint8_t temperature_measure_flag;
void init_sysTick(void);
void delay(int value);



extern uint8_t temp_read;
extern uint8_t time_read;
extern uint8_t light_flag_servo;


extern uint16_t fast_mode_count;




//void SysTick_Handler(void);
