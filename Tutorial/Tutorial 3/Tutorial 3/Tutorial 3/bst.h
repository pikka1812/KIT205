//
//  bst.h
//  Tutorial 3
//
//  Created by Phong on 21/02/2022.
//

#ifndef bst_h
#define bst_h

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct bstNode {
    int data_item;
    struct bstNode *left;
    struct bstNode *right;
} *BSTNodePtr;


typedef struct bst {
    BSTNodePtr root;
} BST;

BST new_bst(void);
BSTNodePtr find_bst_node(BSTNodePtr self, int n);
BSTNodePtr find_bst(BST *self, int);
BSTNodePtr insert_bst_node(BSTNodePtr self, int n);
void insert_bst(BST *self, int n);
BSTNodePtr min_node(BSTNodePtr self);
BSTNodePtr delete_bst_node(BSTNodePtr self, int n);
void delete_bst(BST *self, int n);
void print_pre_order_bst_node(BSTNodePtr self, int depth);
void print_in_order_bst_node(BSTNodePtr self, int depth);
void print_post_order_bst_node(BSTNodePtr self, int depth);
void print_pre_order_bst(BST *self);
void print_in_order_bst(BST *self);
void print_post_order_bst(BST *self);
int height_node(BSTNodePtr self);
int height_tree(BST* self);
#endif /* bst_h */
