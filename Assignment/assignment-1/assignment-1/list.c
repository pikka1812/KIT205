//
//  list.c
//  assignment-1
//
//  Created by Phong on 17/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bst.h"
UnitList new_list() {
    UnitList temp;
    temp.head = NULL;
    return temp;
}

void insert_unit(UnitList *self, String unit_code) {
    ListNodePtr temp = malloc(sizeof(*temp));
    temp->unit_code = unit_code;
    temp->students = new_bst();
    temp->next = NULL;
    
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;
    
    while (current != NULL && strcmp(unit_code, current->unit_code) > 0) {
        prev = current;
        current = current->next;
    }
    if (current == self->head) {
        self->head = temp;
    } else {
        prev->next = temp;
    }
    temp->next = current;
    
}

void delete_unit(UnitList *self, String unit_code) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->unit_code, unit_code) == 0) { // find the unit need to removed
            if (prev == NULL) {    // empty unit list or the unit need to remove is in the first
                self->head = current->next;
            }
            else {
                prev->next = current->next;
            }
            
            // free all the student in the unit that need to removed
            // and then remove the unit node in the list node
            free_tree(&current->students);
            free(current);
            return;
        }
        else {                      // move on
            prev = current;
            current = current->next;
        }
    }
}

void destroy_units_list(UnitList *self) {
    ListNodePtr current = self->head;
    while (current != NULL) {
        ListNodePtr to_free = current;
        current = current->next;
        
        
        free_tree(&to_free->students);
        free(&to_free->unit_code);
        free(to_free);
    }
    self->head = NULL;
}
