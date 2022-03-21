//
//  bst.c
//  assignment-1
//
//  Created by Phong on 17/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"

StudentBST new_bst() {
    StudentBST temp;
    temp.root = NULL;
    return temp;
}

BSTNodePtr find_bst_node(BSTNodePtr self, long student_id){
    if (self == NULL || (student_id == self->student_id)) {
        return self;
    } else if (student_id < self->student_id) {
        return find_bst_node(self->left, student_id);
    } else {
        return find_bst_node(self->right, student_id);
    }
}

BSTNodePtr find_student(StudentBST *self, long student_id) {
  return find_bst_node(self->root, student_id);
}

BSTNodePtr min_node(BSTNodePtr self) {
    BSTNodePtr current = self;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

BSTNodePtr insert_bst_node(BSTNodePtr self, long student_id) {
    if (self == NULL) {
        self = malloc(sizeof(*self));
        self->student_id = student_id;
        self->left = self->right = NULL;
    } else if (student_id < self->student_id) {
        self->left = insert_bst_node(self->left, student_id);
    } else if (student_id > self->student_id) {
        self->right = insert_bst_node(self->right, student_id);
    }
    
    return self;
}

void insert_student(StudentBST *self, long student_id, bool avl) {
    if (avl) {
        self->root = insert_avl_node(self->root, student_id);
    }
    else {
        self->root = insert_bst_node(self->root, student_id);
    }
}

BSTNodePtr delete_bst_node(BSTNodePtr self, long student_id) {
    if (self != NULL) {
        if (student_id == self->student_id) {
            if(self->left != NULL && self->right != NULL) {
                BSTNodePtr successor = min_node(self->right);
                self->student_id = successor->student_id;
                self->right = delete_bst_node(self->right, self->student_id);
            } else {
                BSTNodePtr to_free = self;
                if(self->left) {
                    self = self->left;
                } else {
                    self = self->right;
                }
                free(to_free);
            }
        } else if (student_id < self->student_id) {
            self->left = delete_bst_node(self->left, student_id);
        } else {
            self->right = delete_bst_node(self->right, student_id);
        }
    }
    
    return self;
}


void delete_student(StudentBST *self, long student_id, bool avl) {
    if (avl) {
        self->root = delete_avl_node(self->root, student_id);
    }
    else {
        self->root = delete_bst_node(self->root, student_id);
    }
}

void print_in_order_bst_node(BSTNodePtr self) {
    if(self == NULL) return;
    print_in_order_bst_node(self->left);
    printf("%ld \n", self->student_id);
    print_in_order_bst_node(self->right);
}

void print_students(StudentBST *self) {
    print_in_order_bst_node(self->root);
}

int count_node(BSTNodePtr self) {
    if (self == NULL) return 0;
    return 1 + count_node(self->left) + count_node(self->right);
}

int count_students(StudentBST *self) {
    return count_node(self->root);
}

void free_node(BSTNodePtr self) {
    if (self == NULL) return;
    
    // recursion to go every node in the tree
    free_node(self->left);
    free_node(self->right);
    
    // free memory of the node
    free(self);
}

void free_tree(StudentBST *self) {
    free_node(self->root);
}

int height(BSTNodePtr self) {
    if (self == NULL) {
        return 0;
    }
    return self->height;
}

int balance(BSTNodePtr self) {
    if (self == NULL) {
        return 0;
    }
    return height(self->left) - height(self->right);
}

//         a                               c
//        / \                             / \
//       b   c              =>           a   e
//          / \                         / \
//         d   e                       b   d
BSTNodePtr left_rotate(BSTNodePtr a) {
    BSTNodePtr c = a->right;
    BSTNodePtr d = c->left;
    
    a->right = d;
    c->left = a;
    
    a->height = height(a->left) > height(a->right) ? height(a->left) + 1 : height(a->right) + 1;
    c->height = height(c->left) > height(c->right) ? height(c->left) + 1 : height(c->right) + 1;
    
    return c;
}

//         a                               b
//        / \                             / \
//       b   c              =>           d   a
//      / \                                 / \
//     d   e                               e   c
BSTNodePtr right_rotate(BSTNodePtr a) {
    BSTNodePtr b = a->left;
    BSTNodePtr e = b->right;
    
    a->left = e;
    b->right = a;
    
    a->height = height(a->left) > height(a->right) ? height(a->left) + 1 : height(a->right) + 1;
    b->height = height(b->left) > height(b->right) ? height(b->left) + 1 : height(b->right) + 1;
    
    return b;
}

BSTNodePtr insert_avl_node(BSTNodePtr self, long student_id) {
    if (self == NULL) {
        self = malloc(sizeof(*self));
        self->student_id = student_id;
        self->height = 1;
        self->left = self->right = NULL;
    } else if (student_id < self->student_id) {
        self->left = insert_avl_node(self->left, student_id);
    } else if (student_id > self->student_id) {
        self->right = insert_avl_node(self->right, student_id);
    }
    
    self->height = height(self->left) > height(self->right) ? height(self->left) + 1: height(self->right) +1;
    
    // left tree is unbalance
    if (balance(self) > 1) {
        //left right case => need a left rotate first
        if(student_id > self->left->student_id) {
            self->left = left_rotate(self->left);
        }
        return right_rotate(self);
    }
    
    //right tree is unbalance
    if (balance(self) < -1) {
        //right left case => need a right rotate first
        if(student_id < self->right->student_id) {
            self->right = right_rotate(self->right);
        }
        return left_rotate(self);
    }
    
    return self;
}

BSTNodePtr delete_avl_node(BSTNodePtr self, long student_id) {
    if (self != NULL) {
        if (student_id == self->student_id) {
            if(self->left != NULL && self->right != NULL) {
                BSTNodePtr successor = min_node(self->right);
                self->student_id = successor->student_id;
                self->right = delete_avl_node(self->right, self->student_id);
            } else {
                BSTNodePtr to_free = self;
                if(self->left) {
                    self = self->left;
                } else {
                    self = self->right;
                }
                free(to_free);
                return self;
            }
        } else if (student_id < self->student_id) {
            self->left = delete_avl_node(self->left, student_id);
        } else {
            self->right = delete_avl_node(self->right, student_id);
        }
        
        
        // update the height of node
        self->height = height(self->left) > height(self->right) ? height(self->left) + 1 : height(self->right) + 1;
        
        if (balance(self) > 1) {
            if(balance(self->left) < 0) {
                self->left = left_rotate(self->left);
            }
            return right_rotate(self);
        }
        
        if (balance(self) < -1 ) {
            if(balance(self->right) > 0) {
                self->right = right_rotate(self->right);
            }
            return left_rotate(self);
        }
    }
    
    return self;
}
