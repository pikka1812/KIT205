//
//  list.c
//  Tutorial 1
//
//  Created by Phong on 18/02/2022.
//

#include "list.h"

List new_list() {
    List temp;
    temp.head = NULL;
    return temp;
}

void print_list(List *self) {
    ListNodePtr current = self->head;
    while (current != NULL) {
        printf("%d \n", current->data);
        current = current->next;
    }
    printf("\n");
}

void insert_at_front(List *self, int data) {
    ListNodePtr temp = malloc(sizeof(ListNodePtr));
    temp->data = data;
    temp->next = self->head;
    self->head = temp;
}

void insert_in_order(List *self, int data) {
    ListNodePtr temp = malloc(sizeof(ListNodePtr));
    temp->data = data;
    temp->next = NULL;
    
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;
    
    while (current != NULL && data > current->data) {
        prev = current;
        current = current->next;
    }
    
    if (current == self->head) {
        self->head = temp;
    }
    else {
        prev->next= temp;
    }
    temp->next = current;
}

void delete_list(List *self, int data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;
    
    while (current != NULL) {
        if (current->data == data) { // find the element need to removed
            if (prev == NULL) {    // empty list
                self->head = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        else {                      // move on
            prev = current;
            current = current->next;
        }
    }
}

void destroy_list(List *self) {
    ListNodePtr current = self->head;
    while (current != NULL) {
        ListNodePtr to_free = current;
        current = current->next;
        free(to_free);
    }
    self->head = NULL;
}

List reverse (List *self) {
    // iterative way ( return a new linked list)  :  ( time : O(n), space: O(n) (because brand new list)
    List result = new_list();
    ListNodePtr current = self->head;
    while (current != NULL) {
        insert_at_front(&result, current->data);
        current = current->next;
    }
    return result;
    
    
    // iterative way ( self-reversing ) ( time : O(n) , space: O(1) )
//    ListNodePtr current = self->head;
//    ListNodePtr prev = NULL;
//    ListNodePtr next;
//    while (current != NULL) {
//        next = current->next;
//        current->next = prev;
//        prev = current;
//        current = next;
//    }
//    self->head = prev;
//    return *self;
    
}

List merge(List *f_list, List *s_list) {
    // time : O(a+b) space: O(1)
    List result;
    result.head = malloc(sizeof(ListNodePtr)); // fake vertex
    ListNodePtr a = f_list->head;
    ListNodePtr b = s_list->head;
    ListNodePtr temp = result.head;
    
    while ( a != NULL && b != NULL ) {
        if (a->data > b->data) {
            temp->next = b;
            temp = temp->next;
            b = b->next;
        }
        else {
            temp->next = a;
            temp = temp->next;
            a = a->next;
        }
    }
    if (a == NULL) temp ->next = b;
    else temp->next = a;
    
    result.head = result.head->next;
    return result;
}
