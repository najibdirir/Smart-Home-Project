
typedef struct linkedList_node {
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    float temperaturData;
    struct linkedList_node *next;
} linkedList_node;

extern uint16_t linkedList_node_counter;

linkedList_node* createNode(time_date time_stamp, float sensorData);
void insertFirst(linkedList_node **head, linkedList_node *item);
uint8_t isMember(linkedList_node *head, linkedList_node *item);
void print_linkedList(linkedList_node *head);
uint8_t remove_linkedList_Node(linkedList_node** head, linkedList_node* item);
void free_list(linkedList_node **head);
void sort_linkedList(linkedList_node **head);
void remove_last_LinkedList_node(linkedList_node** head);







