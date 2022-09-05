#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char name[256];
  int date;
} product_data; 

typedef struct linked_list_tag
{
  struct linked_list_tag *next;
  product_data *product; 
} linked_list;


int init (linked_list **head, product_data *head_product)
{
  *head = (linked_list*)malloc(sizeof(linked_list));
  (*head)->next = NULL;
  (*head)->product = head_product;

  return 0;
}

product_data *create_new_product (char name[], int date)
{
  product_data *new_product;
  new_product = (product_data*)malloc(sizeof(product_data));
  strcpy(new_product->name, name);
  new_product->date = date;

  return new_product;
}

linked_list *fetch_tail (linked_list *head)
{
  linked_list *tail;
  if (head == NULL) {
    tail = NULL;
  } else {
    tail = head;
    while (tail->next != NULL) {
      tail = tail->next;
    }
  }

  return tail;
}


linked_list *fetch_pre_tail (linked_list *head)
{
  linked_list *pre_tail;
  if (head == NULL || head->next == NULL) {
    pre_tail = NULL;
  } else {
    pre_tail = head;
    while (pre_tail->next->next != NULL) {
      pre_tail = pre_tail->next;
    }
  }
  return pre_tail;
}


int push (linked_list *head, product_data *new_product)
{
  linked_list *new_tail;
  new_tail = (linked_list*)malloc(sizeof(linked_list));
  new_tail->next = NULL;
  new_tail->product = new_product;

  linked_list *pre_tail;
  pre_tail = fetch_tail(head);
  pre_tail->next = new_tail;  

  return 0;
}

int pop (linked_list **head, product_data *popped_data)
{
  linked_list *current_tail;
  current_tail = fetch_tail(*head);

  linked_list *current_pre_tail;
  current_pre_tail = fetch_pre_tail(*head);

  if (current_tail == NULL) {
    return 0;

  } else if (current_pre_tail == NULL) {
    popped_data = current_tail->product;

    free(current_tail->product);
    free(current_tail);
  
    *head = NULL;

    return 0;

  } else {
    popped_data = current_tail->product;
    current_pre_tail->next = NULL;

    free(current_tail->product);
    free(current_tail);

    return 0;
  }
}


int print_stack (linked_list *head)
{
  if (head == NULL) {
    printf("stack is empty\n");
  } else {
    for (linked_list *current_node = head; ; current_node = current_node->next) {
      printf("name -> %s date -> %d\n", current_node->product->name, current_node->product->date);
      if (current_node->next == NULL) {
        break;
      }
    }
  }

  return 0;
}


int main (void) 
{
  linked_list *head = NULL;
  product_data *init_product_data;
  product_data popped_data;

  
  init_product_data = create_new_product("xyz", 2020);
  init(&head, init_product_data);

  product_data *add_data;
  add_data = create_new_product("aaa", 1111);
  push(head, add_data);
  print_stack(head);
  
  pop(&head, &popped_data);
  print_stack(head);

  pop(&head, &popped_data);
  print_stack(head);

  return 0;
}






