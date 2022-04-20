//
//  bst.h
//  assignment-1
//
//  Created by Phong on 17/03/2022.
//


#ifndef bst_h
#define bst_h

#include <stdbool.h>

typedef struct bstNode {
    long student_id;
    struct bstNode *left;
    struct bstNode *right;
    int height;
} *BSTNodePtr;

typedef struct bst {
    BSTNodePtr root;
} StudentBST;


StudentBST new_bst(void);
BSTNodePtr find_bst_node(BSTNodePtr self, long student_id);
BSTNodePtr find_student(StudentBST *self, long student_id);
BSTNodePtr min_node(BSTNodePtr self);
BSTNodePtr insert_bst_node(BSTNodePtr self, long student_id);
void insert_student_bst(StudentBST *self, long student_id);
BSTNodePtr delete_bst_node(BSTNodePtr self, long student_id);
void delete_student_bst(StudentBST *self, long student_id);
void print_in_order_bst_node(BSTNodePtr self);
void print_students(StudentBST *self);
int count_node(BSTNodePtr self);
int count_students(StudentBST *self);
void free_node(BSTNodePtr self);
void free_tree(StudentBST *self);

int height(BSTNodePtr self);
int balance(BSTNodePtr self);
BSTNodePtr left_rotate(BSTNodePtr a);
BSTNodePtr right_rotate(BSTNodePtr a);
void insert_student_avl(StudentBST *self, long student_id);
BSTNodePtr insert_avl_node(BSTNodePtr self, long student_id);
void delete_student_avl(StudentBST *self, long student_id);
BSTNodePtr delete_avl_node(BSTNodePtr self, long student_id);
#endif /* bst_h */
