#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct node {
  int data;
  struct node* prev;
  struct node* next;
};

// ? System Pointers
struct node* HEAD = NULL;
struct node* BASE = NULL;
struct node* TAIL = NULL;

// ? Insert Operations
void prepend(int data) {
  struct node* nn = (struct node*) malloc(sizeof(struct node));
  nn->data = data;
  if (HEAD == NULL || TAIL == NULL) {
    HEAD = nn;
    TAIL = nn;
    BASE = nn; // save first pointer during first allocation
    nn->next = nn;
    nn->prev = nn;
  } else {
    nn->next = HEAD;
    nn->prev = TAIL;
    nn->next->prev = nn;
    HEAD->prev = nn;
    TAIL->next = nn;
    HEAD = nn;
  }
}
void append(int data) {
  struct node* nn = (struct node*) malloc(sizeof(struct node));
  nn->data = data;
  if (HEAD == NULL || TAIL == NULL) {
    HEAD = nn;
    TAIL = nn;
    BASE = nn; // save first pointer during first allocation
    nn->next = nn;
    nn->prev = nn;
  } else {
    struct node* cn = HEAD;
    while (cn != TAIL) {
      cn = cn->next;
    }
    nn->prev = cn;
    nn->next = HEAD;
    cn->next = nn;
    TAIL->next = nn;
    HEAD->prev = nn;
    TAIL = nn;
  }
}
void insertAt(int pos, int data) {} // TODO

// ? Delete Operations
void removeLast() {
  if (TAIL == NULL) {
    return;
  }
  if (TAIL == HEAD) {
    free(TAIL);
    HEAD = NULL;
    TAIL = NULL;
  } else {
    struct node* TEMP = TAIL;
    TAIL = TAIL->prev;
    TAIL->next = HEAD;
    HEAD->prev = TAIL;
    free(TEMP);
  }
}
void removeFirst() {
  if (HEAD == NULL) {
    return;
  }
  if (HEAD == TAIL) {
    // only one element
    free(HEAD);
    HEAD = NULL;
    TAIL = NULL;
  } else {
    struct node* TEMP = HEAD;
    HEAD = HEAD->next;
    HEAD->prev = TAIL;
    TAIL->next = HEAD;
    free(TEMP);
  }
  
}
void removeAt(size_t index) {
  if (HEAD == NULL) {
    return;
  }
  struct node* cn = HEAD;
  for (size_t i = 0; i < index; i++)
  {
    cn = cn->next;
  }
  if(cn == HEAD) {
    removeFirst();
  }
  else if (cn == TAIL) {
    removeLast();
  } else {
    cn->next->prev = cn->prev;
    cn->prev->next = cn->next;
    free(cn);
  }
}

// TODO: Traversal

// ? Other
void search(int value) {} // TODO
void find(int value) {} // TODO

// ? Utils
void printList() {
  if (HEAD == NULL) {
    printf("List empty.\n");
    return;
  }
  struct node* cn = HEAD;
  printf("[");
  do {
    printf("%d, ", cn->data);
    cn = cn->next;
  } while (cn != HEAD);
  printf("]\n");
}
void status() {
  if (HEAD == NULL) {
    return;
  }
  struct node* cn = HEAD;
  printf(" Value |    Address     |  Prev Address  |  Next Address  | [HTPN] \n");
  printf("-------+----------------+----------------+----------------+--------\n");
  do {
    printf(" %5d | %14p | %14p | %14p | ", cn->data, cn, cn->prev ,cn->next);
    printf("[");
    if(cn == HEAD) {
      printf("H");
    } else {
      printf("-");
    }
    if(cn == TAIL) {
      printf("T");
    } else {
      printf("-");
    }
    if(cn->prev->next == cn) {
      printf("P");
    } else {
      printf("-");
    }
    
    if(cn->next->prev == cn) {
      printf("N");
    } else {
      printf("-");
    }
    printf("]\n");
    
    cn = cn->next;
  } while(cn != HEAD);
  printf("-----------------------------------------------------------------\n");
  printf("HEAD: %14p\nTAIL: %14p\n",HEAD,TAIL);
}

int main() {
  for (int i = 0; i < 5; i++)
  {
    append(i);
  }
  prepend(5);
  
  removeAt(0);

  status();
  printList();
  return EXIT_SUCCESS;
}