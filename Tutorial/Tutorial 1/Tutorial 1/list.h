//
//  list.h
//  Tutorial 1
//
//  Created by Phong on 18/02/2022.
//

#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>


typedef struct listNode{
    int data;
    struct listNode *next;
} *ListNodePtr;

typedef struct list {
    ListNodePtr head;
} List;

List new_list(void);
void print_list(List *self);
void insert_at_front(List *self, int data);
void insert_in_order(List *self, int data);
void delete_list(List *self, int data);
void destroy_list(List *self);
List reverse (List *self);
List merge(List *f_list, List *s_list);
#endif /* list_h */
