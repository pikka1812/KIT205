//
//  main.c
//  assignment-1
//
//  Created by Phong on 17/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "bst.h"


void option_add_unit(UnitList *self) {
    char buffer[100];
    String unit_code;
    
    printf("Enter the unit code: ");
    scanf("%s", buffer);
    
    unit_code = malloc(strlen(buffer) +1);
    strcpy(unit_code, buffer);
    
    insert_unit(self, unit_code);
}

void option_remove_unit(UnitList *self) {
    char buffer[100];
    String unit_code;
    
    printf("Enter the unit code: ");
    scanf("%s", buffer);
    
    unit_code = malloc(strlen(buffer) +1);
    strcpy(unit_code, buffer);
    
    delete_unit(self, unit_code);
}

void option_enrol_student(UnitList *self, bool avl) {
    long student_id;
    char buffer[100];
    String unit_code;
    
    printf("Enter the student id: ");
    scanf("%ld", &student_id);
    printf("Enter the unit code: ");
    scanf("%s", buffer);
    
    unit_code = malloc(strlen(buffer) +1);
    strcpy(unit_code, buffer);
    
    ListNodePtr current = self->head;
    
    while(current != NULL && strcmp(current->unit_code, unit_code) != 0) {
        current = current->next;
    }
    
    if(current != NULL) {
        if (avl) insert_student_avl(&current->students, student_id);
        else insert_student_bst(&current->students, student_id);
    }
    
    free(unit_code);
}

void option_unenrol_student(UnitList *self, bool avl) {
    long student_id;
    char buffer[100];
    String unit_code;
    ListNodePtr current = self->head;
    
    printf("Enter the student id: ");
    scanf("%ld", &student_id);
    printf("Enter the unit code: ");
    scanf("%s", buffer);
    
    unit_code = malloc(strlen(buffer) +1);
    strcpy(unit_code, buffer);
    
    while(current != NULL && strcmp(current->unit_code, unit_code) != 0) {
        current = current->next;
    }
    
    if(current != NULL) {
        if (avl) delete_student_avl(&current->students, student_id);
        else delete_student_bst(&current->students, student_id);
    }
    
    free(unit_code);
}

void option_print_all_units(UnitList *self) {
    ListNodePtr current = self->head;
    
    printf("Unit enrolments: \n");
    while (current != NULL) {
        printf("%s %d \n", current->unit_code, count_students(&current->students));
        current = current->next;
    }
}

void option_print_unit(UnitList *self) {
    ListNodePtr current = self->head;
    char buffer[100];
    String unit_code;
    
    printf("Enter the unit code: ");
    scanf("%s", buffer);
    
    unit_code = malloc(strlen(buffer) +1);
    strcpy(unit_code, buffer);
    
    while(current != NULL && strcmp(current->unit_code, unit_code) != 0) {
        current = current->next;
    }
    
    if (current != NULL) {
        printf("List of students enrol in %s: \n" , unit_code);
        print_students(&current->students);
    }
    
    free(unit_code);
}

void option_print_student(UnitList *self) {
    ListNodePtr current = self->head;
    long student_id;
    
    printf("Enter the student id: ");
    scanf("%ld", &student_id);
    
    printf("List of units student \"%ld\" enrol in: \n", student_id);
    while(current != NULL) {
        if(find_student(&current->students, student_id) != NULL) {
            printf("%s \n", current->unit_code);
        }
        current = current->next;
    }
}




int main(int argc, const char * argv[]) {    
    UnitList units_list = new_list();
    int quit = 0;
    bool avl = true; // change this bool to switch between avl tree and bst tree
    
    while (!quit) {
        int option;
        printf("Choose the option: ");
        scanf("%d", &option);

        switch(option) {
            case 0: quit = 1;
                break;
            case 1:
                option_add_unit(&units_list);
                break;
            case 2:
                option_remove_unit(&units_list);
                break;
            case 3:
                option_enrol_student(&units_list, avl);
                break;
            case 4:
                option_unenrol_student(&units_list, avl);
                break;
            case 5:
                option_print_all_units(&units_list);
                break;
            case 6:
                option_print_unit(&units_list);
                break;
            case 7:
                option_print_student(&units_list);
                break;
        }
    }
    destroy_units_list(&units_list);
}
