#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hashtable.h"

int main(){
	int command = 1;
	HashTable table = create_hashtable(11);
	char buffer[100];
    String input = malloc(sizeof(input)) ;

	while (command){
		scanf("%d", &command);
		switch (command){
		case 1:
            printf("Enter the input: ");
			scanf("%s", input);
			hash_insert(&table, input);
			break;
		case 2:
            printf("Enter the input: ");
            scanf("%s", input);
                hash_remove(&table, input);
            break;
		case 3:
            hash_print(&table);
			break;
		}
		printf("\n");
	}
	// TODO: destroy
}
