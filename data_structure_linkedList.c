#include "One_for_all_header.h"


uint16_t linkedList_node_counter = 0;

/*This will create a linkedlist node with the hitemp of malloc*/
linkedList_node* createNode(time_date time_stamp, float sensorData){
     linkedList_node *node = (linkedList_node*)malloc(sizeof(linkedList_node));
    if (node == NULL) {
      return NULL;
    }
    node->day = time_stamp.day;
    node->hour = time_stamp.hour;
    node->min = time_stamp.minute;
    node->sec = time_stamp.second;
    node->temperaturData = sensorData;
    node->next = NULL;
    return node;
}

/*THis function will put a linkedList node to a linked List*/
void insertFirst(linkedList_node **head, linkedList_node *item) {
    item->next = *head;
    *head = item;
    linkedList_node_counter ++;
}

/*Go through the linkedList to find a node*/
uint8_t isMember(linkedList_node *head, linkedList_node *item) {
    linkedList_node *current = head;
    while (current != NULL){
        if (current->day == item->day && 
            current->hour == item->hour && 
            current->min == item->min && 
            current->sec == item->sec){
            return 1;
        }
        current = current->next;
    }
    return 0;
}


/*Print the linkedList */
void print_linkedList(linkedList_node *head){
    linkedList_node *current = head;
    clear_display_text();
    while (current != NULL) {
      data_2_display(0x00); //Character 'Space'
      command_2_display(0xC0);  
      print_float_2_display(current->temperaturData);    
      data_2_display(0x00); //Character 'Space'
      command_2_display(0xC0);  
        current = current->next;
    }
}


/*Remove a linked List node from a linked List*/
uint8_t remove_linkedList_Node(linkedList_node** head, linkedList_node* item){
    if (head == NULL || item == NULL) {
        return -1;
    }
    if (*head == item) {
        *head = item->next;
        free(item);
        linkedList_node_counter--;
        return 0; // success
    }
    linkedList_node *current = *head;

    while (current->next != NULL && current->next != item) {
        current = current->next;
    }
    if (current->next == item) {
        current->next = item->next;
        free(item); 
        linkedList_node_counter--;
        return 0; //success
    }
    return -1;
}



/*This will free all element from the list*/ 
void free_list(linkedList_node **head){
    linkedList_node  *current = *head;
    linkedList_node  *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
        linkedList_node_counter --;
    }
    *head = NULL; 
}


/*THis will sort the linked List*/
void sort_linkedList(linkedList_node **head) {
  if (!head || !*head){
    return; 
  }
    linkedList_node *sorted = NULL;
    while (*head) {
        linkedList_node **current = head;
        linkedList_node *entry = *head;
        linkedList_node **smallest = head;
        
        // Find the smallest value in the list
        while (entry) {
            if (entry->temperaturData < (*smallest)->temperaturData) {
                smallest = current;
            }
            current = &entry->next;
            entry = entry->next;
        }   
        // Remove 'smallest' from the list
        entry = *smallest;
        *smallest = entry->next;
        // Insert 'smallest' into the 'sorted' list
        entry->next = sorted;
        sorted = entry;
    }
    *head = sorted;
}


/*TO remove the head added node or last node in the linked list*/
void remove_last_LinkedList_node(linkedList_node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        if (*head) {
            free(*head);
            *head = NULL;
            linkedList_node_counter--;
        }
        return;
    }
    linkedList_node *current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    linkedList_node_counter--;
}
