//
//  main.c
//  Tutorial 1
//
//  Created by Phong on 18/02/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void option_insert(List *self) {
    int inputNum;
    printf("Number for insert: ");
    scanf("%d", &inputNum);
    
    insert_at_front(self, inputNum);
}

void option_delete(List *self) {
    int inputNum;
    printf("Number for delete: ");
    scanf("%d", &inputNum);
    
    delete_list(self, inputNum);
}

void option_print(List *self){
    print_list(self);
}

int main(int argc, const char * argv[]) {
//    List my_list = new_list();
//    int quit = 0;
//    while (!quit) {
//        int option;
//        printf("Choose the option: ");
//        scanf("%d", &option);
//
//        switch(option) {
//            case 0: quit = 1;
//                break;
//            case 1:
//                option_insert(&my_list);
//                break;
//            case 2:
//                option_delete(&my_list);
//                break;
//            case 3:
//                option_print(&my_list);
//                break;
//        }
//    }
//    destroy_list(&my_list);
    
//    Tesing infrastructe 1,2;
//    List my_list = new_list();
//    int input;
//    scanf("%d", &input);
//    while (input != 0) {
//        insert_at_front(&my_list, input);
//        scanf("%d", &input);
//    }
//    printf("After insert done: \n" );
//    print_list(&my_list);
//    destroy_list(&my_list);
//    printf("After destroy: ");
//    print_list(&my_list);
    
//    Tesing linked list:
    List my_list = new_list();
    List s_list = new_list();
    insert_at_front(&my_list, 4);
    insert_in_order(&my_list, 3);
    insert_in_order(&my_list, 5);
    insert_in_order(&my_list, 6);
    insert_in_order(&my_list, 7);
    insert_in_order(&my_list, 1);
    delete_list(&my_list, 3);
    print_list(&my_list);
    //List reverse_list = reverse(&my_list);
    //destroy_list(&my_list);
    //print_list(&reverse_list);
    //print_list(&my_list);
    
    insert_in_order(&s_list, 2);
    insert_in_order(&s_list, 3);
    insert_in_order(&s_list, 8);
    insert_in_order(&s_list, 9);
    print_list(&s_list);
    
    List merge_list = merge(&my_list, &s_list);
    print_list(&merge_list);
    return 0;
}
