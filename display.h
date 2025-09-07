void display_init(void);
void command_2_display(unsigned char command);
void data_2_display(unsigned char data);
unsigned char read_display_status(void);
void clear_display_text(void);
void set_pointer_at(uint16_t data_1, uint16_t data_2);
void clear_display_graphic(void);
void draw_line (uint16_t row_position, uint16_t index_position,  uint8_t data, uint16_t line);
void clear_specific_area(uint8_t data1, uint8_t data2, uint16_t index_to_delete);
void hardware_init(void);
void GPIO_config(void);






