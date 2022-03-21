//
//  list.h
//  assignment-1
//
//  Created by Phong on 17/03/2022.
//

#ifndef list_h
#define list_h

#include "bst.h"

typedef char* String;

typedef struct listNode{
    String unit_code;
    StudentBST students;
    struct listNode *next;
} *ListNodePtr;

typedef struct list {
    ListNodePtr head;
} UnitList;


UnitList new_list(void);
void insert_unit(UnitList *self, String unit_code);
void delete_unit(UnitList *self, String unit_code);
void destroy_units_list(UnitList *self);

#endif /* list_h */
