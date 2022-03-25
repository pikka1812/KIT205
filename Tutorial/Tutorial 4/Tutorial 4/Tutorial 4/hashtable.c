#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

HashTable create_hashtable(int n){
    HashTable *newtable = malloc(sizeof(HashTable));
    List *table = malloc(n * sizeof(List));
    
    
    for(int i = 0; i < n; i++) {
        table[i] = new_list();
    }

    newtable->size = n;
    newtable->table = table;
    
	return *newtable;
}

int hash(String key, int size){
	unsigned long h = 0; // unsigned long, so that when it wraps it's still positive
	long n = strlen(key);

	for (int i = 0; i < n; i++){
		// multiply by 32 (<<5) and add ascii value
		h = (h << 5) + (int)(key[i]);
	}
	return h%size;
}

void hash_insert(HashTable *self, String key){
    int hashKey = hash(key, self->size);
    insert_at_front(&(self->table[hashKey]), key);
}

void hash_remove(HashTable *self, String key){
    int hashKey = hash(key, self->size);
    delete_from_list(&(self->table[hashKey]), key);
}

void hash_print(HashTable *self){
	for (int i = 0; i < self->size; i++){
		printf("%d: ", i);
		print_list(&(self->table[i]));
	}
}

void hash_destroy(HashTable *self){
	// TODO
}
