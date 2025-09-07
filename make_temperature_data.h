void N_recording(void);
void record_N_temp_fast_mode(void);
typedef struct temp_data_day{
    linkedList_node *max_temp;
    linkedList_node *min_temp;
    float avg_temp;
} temp_data_day;
extern linkedList_node *temperature_data_7_days;
void print_temperature_linkedList_2_display(temp_data_day day_temp , uint8_t display_index, uint8_t day);
extern uint8_t N;
extern uint8_t N_checker;
extern uint8_t fast_mode_flag;
extern uint8_t sec_counter;
extern linkedList_node *temp_N_recordings;
void row_index_fix(uint16_t check);




/*-------------------------------------------------*/



//

//extern linkedList_node *fast_mode;
//extern uint8_t temp_switch;
//extern temp_data_day current_day;
//
//
////extern double totala_temperatur;
//extern int totala_noder_en_dag;
//extern linkedList_node* maximum_temp;
//extern linkedList_node* minsta_temp;
//
//void record_temp_minute(void);
//void temperature_N_recording(void);
//void create_Daily(void);
//void record_temp_fast_mode(void);
//void req_3_and_9_fastmode(linkedList_node *linkedList);
//
//void make_record_every(uint16_t amount);
