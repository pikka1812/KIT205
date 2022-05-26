//
//  main.c
//  Tutorial 7
//
//  Created by Phong on 28/04/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void insert_at_front(EdgeList *list, Edge node) {
    EdgeNodePtr temp = malloc(sizeof(EdgeNodePtr));
    temp->edge = node;
    temp->next = list->head;
    list->head = temp;
}

void print_pagerank(Graph self, int *out_degrees,float d, int iterations) {
    int pagerank[iterations];
    int *sum;
    for (int i = 0; i < iterations; i++) {
        sum = calloc(self.V, sizeof(int));
        for (int i = 0; i < self.V; i++) {
            
        }
        
        for (int i = 0; i < self.V; i++) {
            
        }
    }
    
    
}

int main(int argc, const char * argv[]) {
    Graph G;
    int* out_degrees;
    
    
    freopen("input.txt", "r", stdin);
    scanf("%d", &(G.V));
    G.edges = malloc(G.V * sizeof(EdgeList));
    out_degrees = calloc(G.V, sizeof(int));
    
    for (int i = 0; i < G.V ; i++) {
        scanf("%d", &out_degrees[i]);
        G.edges[i].head = NULL;
        
        for (int j = 0; j < out_degrees[i]; j++) {
            Edge new_edge;
            scanf("%d,%d", &(new_edge.to_vertex), &(new_edge.weight));
            insert_at_front(&G.edges[i], new_edge);
        }
    }

    print_pagerank(G, out_degrees, 0.5, 1);
    
    

}
