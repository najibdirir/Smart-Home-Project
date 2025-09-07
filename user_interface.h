

typedef enum {
    STATE_HOME_PAGE,
    STATE_TEMPERATURE_PAGE,
    STATE_SHADING_SYSTEM_PAGE,
    STATE_CALENDAR_PAGE,
    STATE_SETTINGS_PAGE
} Application_State;

extern Application_State currentState;

extern uint8_t key;
extern uint8_t force_exit;
extern uint8_t show_data;
void home_page(void);
void page_control(void);
void temp_page(void);
extern uint8_t force_exit;

