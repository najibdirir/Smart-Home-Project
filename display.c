#include "One_for_all_header.h"

#define databus 0x3FC
#define CE (1<<15)
#define C_D (1<<14)
#define RD (1<<16)
#define WR (1<<17)
#define RESET (1<<0)
#define DIR (1<<13)
#define BLOCK_C_D (3<<13)
#define OE (1<<12)


void hardware_init(void){
  light_sensor_init();
  servo_init();
  temperature_init();
  keypad_init();
  GPIO_config();
  display_init();
  Led_init(); 
  clear_display_text();
  clear_display_graphic();
}


void GPIO_config(void){
  *AT91C_PIOC_PER = databus;
  *AT91C_PIOC_PER = DIR;
  *AT91C_PIOC_PER = OE;
  *AT91C_PIOC_OER = OE;
  *AT91C_PIOC_PER = C_D;
  *AT91C_PIOC_OER = C_D;
  *AT91C_PIOC_PER = CE;
  *AT91C_PIOC_OER = CE;
  *AT91C_PIOC_PER = RD;
  *AT91C_PIOC_OER = RD;
  *AT91C_PIOC_PER = WR;
  *AT91C_PIOC_OER = WR;
  *AT91C_PIOD_PER = RESET;
  *AT91C_PIOD_OER = RESET;
}


/*This will write command to the dispay*/
void command_2_display(unsigned char Command){
  //Wait until Read_Status_Display returns an OK
 while((read_display_status() & (0x3)) != 0x3){} 
  *AT91C_PIOC_CODR = databus;
  *AT91C_PIOC_SODR = (Command<<2);
  *AT91C_PIOC_OER = DIR;
  *AT91C_PIOC_CODR = DIR; 
  *AT91C_PIOC_CODR = OE;
  *AT91C_PIOC_OER = databus;
  *AT91C_PIOC_SODR = C_D; 
  *AT91C_PIOC_CODR = CE; 
  *AT91C_PIOC_CODR = WR; 
  delay(1000);
  *AT91C_PIOC_SODR = CE; 
  *AT91C_PIOC_SODR = WR;
  *AT91C_PIOC_SODR = OE;
  *AT91C_PIOC_ODR = databus;
}

/*This will write data to the display*/
void data_2_display(unsigned char Data){
  //wait until Read_Status_Display returns an ok
  while((read_display_status() & 0x3) != 0x3){}
  *AT91C_PIOC_OER = databus;
  *AT91C_PIOC_CODR = databus;
  *AT91C_PIOC_SODR = Data<<2;
  *AT91C_PIOC_OER = DIR;
  *AT91C_PIOC_CODR = DIR;
  *AT91C_PIOC_CODR = OE;
  *AT91C_PIOC_OER = databus;
  *AT91C_PIOC_CODR = C_D;
  *AT91C_PIOC_CODR = CE;
  *AT91C_PIOC_CODR = WR;
  delay(21);
  *AT91C_PIOC_SODR = CE;
  *AT91C_PIOC_SODR = WR;
  *AT91C_PIOC_SODR = OE;
  *AT91C_PIOC_ODR = databus;
}

/*This will read the status of the display*/
unsigned char read_display_status(void){
  unsigned char temp;
  *AT91C_PIOC_ODR = databus;
  *AT91C_PIOC_OER = DIR;
  *AT91C_PIOC_SODR = DIR;
  *AT91C_PIOC_CODR = OE;
  *AT91C_PIOC_SODR = C_D;
  *AT91C_PIOC_CODR = CE;
  *AT91C_PIOC_CODR = RD;
  delay(21);
  temp = (*AT91C_PIOC_PDSR>>2);
  *AT91C_PIOC_SODR = CE;
  *AT91C_PIOC_SODR = RD;
  *AT91C_PIOC_SODR = OE;
  *AT91C_PIOC_CODR = DIR;
  return temp;
}


void display_init(void){
  *AT91C_PIOD_CODR = RESET;
  delay(10000);
  *AT91C_PIOD_SODR = RESET;
  /*The text home address is set to 0x00*/
  data_2_display(0x00);
  data_2_display(0x00);
  command_2_display(0x40);
  /*The graphic home address is set to 0x4000*/
  data_2_display(0x00);
  data_2_display(0x40);
  command_2_display(0x42); 
  /*We have chosen to have 40 characters in one row*/
  data_2_display(0x28);
  data_2_display(0x00);
  command_2_display(0x41); //Set text area
  
  data_2_display(0x28);
  data_2_display(0x00);
  command_2_display(0x43); //Set graphic area
  
  command_2_display(0x81); 
  command_2_display(0x9C);// both text and graphic are on 
  //reverse screen
  data_2_display(0x01);
  data_2_display(0x00);
  command_2_display(0xD0); 
}
/*This will enable us to move the pointer at some address*/
void set_pointer_at(uint16_t data_1, uint16_t data_2){
  data_2_display(data_2);
  data_2_display(data_1);    
  command_2_display(0x24);
} 

/*This will only clear text from display by printing space*/
void clear_display_text(void){     
  set_pointer_at(0x00,0x00);
  for(uint16_t i = 0; i<640; i++){ 
        data_2_display(0x00);
        command_2_display(0xC0);
    }
   set_pointer_at(0x00,0x00);
   cursor_index_counter=0;
   x = 0;
}

/*This will only clear the graphic on display*/
void clear_display_graphic(void){
  int addr = 0x4000;
  data_2_display(addr&0xff);
  data_2_display((addr>>8)&0xff);
  command_2_display(0x24);
  for(uint16_t i = 0; i<40*8*16; i++){ 
       data_2_display(0x00);
       command_2_display(0xC0);
  }
}

/*This will draw graphic using dots and adress*/
void draw_line (uint16_t row_position, uint16_t index_position,  uint8_t data, uint16_t line){
  int addr = 0x4000+(index_position+(320*row_position)); //int addr = 0x4000+(position*8);
  data_2_display(addr&0xff);
  data_2_display((addr>>8)&0xff);
  command_2_display(0x24);
  for(uint16_t i = 0; i<(line); i++){ //640 antal 
       data_2_display(data); 
       command_2_display(0xC0);
       addr += (0x28);
       data_2_display(addr&0xff);      
       data_2_display((addr>>8)&0xff);
       command_2_display(0x24);     
  }
  set_pointer_at(0x0, 0x0);
}


/*This will delete a specific area from the display*/
void clear_specific_area(uint8_t data1, uint8_t data2, uint16_t index_to_delete){
  set_pointer_at(data1, data2);
  for(uint16_t i = 0; i< index_to_delete; i++){
    data_2_display(0x00); //Character 'Space'
    command_2_display(0xC0);
  }
  set_pointer_at(data1, data2);
}



