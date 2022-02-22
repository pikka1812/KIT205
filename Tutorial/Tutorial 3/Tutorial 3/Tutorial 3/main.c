//
//  main.c
//  Tutorial 3
//
//  Created by Phong on 21/02/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(int argc, const char * argv[]) {
    BST tree = new_bst();
    int quit = 0;
    int data;
    while (!quit) {
        printf("Enter data: ");
        scanf("%d", &data);
        if(data != 0) insert_bst(&tree, data);
        else quit = 1;
    }
    printf("Pre-order tree: (Data->Left->Right) \n");
    print_pre_order_bst(&tree); 
    printf("\n");
    
    printf("In-order tree: (Left->Data->Right) \n");
    print_in_order_bst(&tree);
    printf("\n");
    
    printf("Post-order tree: (Left->Data->Right) \n");
    print_post_order_bst(&tree);
    printf("\n");
    
    printf("Height : %d \n", height_tree(&tree));
    
    return 0;
}
