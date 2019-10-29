#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct skip_node{
  int element;
  struct skip_node *prev;
  struct skip_node *next;
  struct skip_node *down;
  struct skip_node *up;
}S_NODE;

typedef struct head_tail{
  S_NODE *head;
  S_NODE *tail;
}head_tail;

int insert_node(int, int);
void add_level();
void print_skip_list();
int search_skip(int);
void delete_skip(int);
void submap(int, int);

head_tail top_head_tail;

int main(void){

  int num_levels = 1;

  srand(time(0));

  add_level();
  add_level();
  top_head_tail.head->down->up = top_head_tail.head;
  top_head_tail.tail->down->up = top_head_tail.tail;

  int element = 0;

  while(element != -1){
    printf("Enter num to insert: ");
    scanf("%d", &element);
    if(element != -1){
      num_levels = insert_node(element, num_levels);
    }
  }

  print_skip_list();


  printf("Enter num to search: ");
  scanf("%d", &element);
  if(search_skip(element) == 1){
    printf("\nDeleting all %d nodes...\n", element);
    delete_skip(element);
    print_skip_list();
  }

  int k1, k2;

  printf("\nEnter submap (k1 k2): ");
  scanf("%d %d", &k1, &k2);
  printf("Submap from %d to %d:\n", k1, k2);
  submap(k1, k2);


  return 0;
}

int insert_node(int new_element, int num_levels){

  int coin_flip_counter = 0, coin_flip_value = 0;
  S_NODE *current = top_head_tail.head;

  while(new_element >= current->next->element || current->down != NULL){
    if(new_element >= current->next->element){
      current = current->next;
    } else {
      if(current->down != NULL){
        current = current->down;
      }
    }
  }

  S_NODE *temp_heads = top_head_tail.head;

  S_NODE *new = (S_NODE *) malloc(sizeof(S_NODE));
  new->up = NULL;
  new->down = NULL;
  new->next = current->next;
  new->prev = current;
  new->element = new_element;

  current->next = new;
  new->next->prev = new;

  S_NODE *lower_level_new_node = new;

  coin_flip_value = rand() % 2;
  while(coin_flip_value == 1){
    coin_flip_counter++;
    coin_flip_value = rand() % 2;
  }

  S_NODE *prev_node = lower_level_new_node->prev;

  for(int i = 0; i < coin_flip_counter; i++){

    S_NODE *new = (S_NODE *) malloc(sizeof(S_NODE));
    new->up = NULL;
    new->down = lower_level_new_node;
    lower_level_new_node->up = new;
    new->element = new_element;

    if(i >= num_levels - 1){
      add_level();
      top_head_tail.head->down->up = top_head_tail.head;
      top_head_tail.tail->down->up = top_head_tail.tail;
      num_levels++;
    }

    while(prev_node->up == NULL){
      prev_node = prev_node->prev;
    }
    prev_node = prev_node->up;

    new->next = prev_node->next;
    new->prev = prev_node;
    prev_node->next = new;

    lower_level_new_node = lower_level_new_node->up;
    prev_node = lower_level_new_node->prev;

  }

  return num_levels;

}

void add_level(){

    S_NODE *sX_head = (S_NODE *) malloc(sizeof(S_NODE));
    sX_head->up = NULL;
    sX_head->down = top_head_tail.head;
    sX_head->next = NULL;
    sX_head->prev = NULL;
    sX_head->element = INT_MIN;

    S_NODE *sX_tail = (S_NODE *) malloc(sizeof(S_NODE));
    sX_tail->up = NULL;
    sX_tail->down = top_head_tail.tail;
    sX_tail->next = NULL;
    sX_tail->prev = sX_head;
    sX_tail->element = INT_MAX;

    sX_head->next = sX_tail;

    top_head_tail.head = sX_head;
    top_head_tail.tail = sX_tail;
}

void print_skip_list(){

  S_NODE *temp = top_head_tail.head;
  S_NODE *temp_heads = top_head_tail.head;

  while(temp){

    if(temp->element == INT_MIN){
      printf("-INF->");
    } else {
      if(temp->element == INT_MAX){
        printf("INF");
      } else {
        printf("%d->", temp->element);
      }
    }

    if(temp->next == NULL){
      printf("\n");
      temp = temp_heads->down;
      temp_heads = temp_heads->down;
    } else {
      temp = temp->next;
    }

  }

  return;
}

int search_skip(int new_element){

  S_NODE *current = top_head_tail.head;

  while(new_element != current->element || new_element >= current->next->element || current->down != NULL){
    if(new_element == current->element){
      printf("%d found!", current->element);
      return 1;
    }
    if(new_element >= current->next->element){
      current = current->next;
    } else {
      if(current->down != NULL){
        current = current->down;
      } else {
        printf("%d not fount. floor = %d, ceiling = %d", new_element, current->element, current->next->element);
        return 0;
      }
    }
  }

}

void delete_skip(int new_element){

  S_NODE *current = top_head_tail.head;

  while(new_element != current->element || new_element >= current->next->element || current->down != NULL){
    if(new_element == current->element){
      break;
    }
    if(new_element >= current->next->element){
      current = current->next;
    } else {
      if(current->down != NULL){
        current = current->down;
      }
    }
  }

  while(current->down){
    current = current->down;
  }

  S_NODE *temp = current;
  S_NODE *temp_head = top_head_tail.head->down;
  S_NODE *temp_tail = top_head_tail.tail->down;

  while(current){
    temp = current->up;
    if(current->prev->element == INT_MIN && current->next->element == INT_MAX){
      free(top_head_tail.head);
      free(top_head_tail.tail);
      top_head_tail.head = temp_head;
      top_head_tail.tail = temp_tail;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    current = temp;
  }

}

void submap(int k1, int k2){

  S_NODE *current = top_head_tail.head;

  while(k1 != current->element || k1 >= current->next->element || current->down != NULL){
    if(k1 == current->element){
      break;
    }
    if(k1 >= current->next->element){
      current = current->next;
    } else {
      if(current->down != NULL){
        current = current->down;
      }
    }
  }

  while(current->down){
    current = current->down;
  }

  while(current->element != k2){
    printf("%d->", current->element);
    current = current->next;
  }
  printf("%d", current->element);

}
