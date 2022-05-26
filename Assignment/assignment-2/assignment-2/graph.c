#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "graph.h"


// insert_at_front
void insert_edge(EdgeList* self, Edge e){  
	EdgeNodePtr new_node = malloc(sizeof * new_node);
	new_node->edge = e;
	new_node->next = self->head;
	self->head = new_node;
}

// insert_at_rear
void enqueue(EdgeList* self, Edge e) {
    EdgeNodePtr new_node = malloc(sizeof * new_node);
    EdgeNodePtr current = self->head;
    new_node->edge = e;
    new_node->next= NULL;
    
    //empty queue
    if (current == NULL) {
        self->head = new_node;
    } else {
        // loop to the last element of queue
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// remove from front (and return value)
Edge dequeue(EdgeList* self) {
    EdgeNodePtr temp = self->head; // temporary pointer to the head for freeing later
    Edge edge = temp->edge; // edge return
    self->head = self->head->next;
    
    //free the remove head memory
    free(temp);
    
    return edge;
}

// Breadth First Search that stores edges in visited order as an edgelist
// Edge weight will store the distance from the start vertex
EdgeList bfs(Graph* self, int start) {
    int *visited = calloc(self->V, sizeof(int));
    EdgeList *list = malloc(sizeof(EdgeList));
    EdgeList *process_list = malloc(sizeof(EdgeList));
    
    Edge first;
    
    visited[start] = 1;
    first.to_vertex = start;
    first.weight = 0;
    enqueue(process_list, first);
    
    // check for empty
    while (process_list->head != NULL) {
        Edge curr_process = dequeue(process_list);
        EdgeNodePtr iteration = self->edges[curr_process.to_vertex].head;
        while(iteration != NULL) {
            Edge temp = iteration->edge;
            temp.weight = curr_process.weight + 1;
            if(!visited[temp.to_vertex]) {
                enqueue(process_list, temp);
                visited[temp.to_vertex] = 1;
            }
            
            iteration = iteration->next;
        }
        enqueue(list, curr_process);
    }
    free(process_list);
    free(visited);
    
    return *list;
}

// calculate centrality based on eigenvector method
double* centrality(Graph* self) {
    double *eigen = malloc(self->V * sizeof(double));
    int *out_degrees = calloc(self->V , sizeof(int));
    double *a = malloc(self->V * sizeof(double));
    // calculate out degrees of each vertex
    for (int i = 0; i < self->V; i++) {
        EdgeNodePtr current = self->edges[i].head;
        while(current!= NULL) {
            out_degrees[i]++;
            current = current->next;
        }
    }
    
    // init some needed array
    for (int i = 0; i < self->V; i++) {
        eigen[i] = 1;
        a[i] = out_degrees[i];
    }
    
    // calculate eigenvector
    for (int i = 0; i < 10; i++){
        long double total_degrees = 0;
        double normalized_value;
        for (int j =0 ; j < self->V; j++) {
            total_degrees += a[j]*a[j];
        }
        normalized_value = sqrt(total_degrees);
        
        for (int k = 0; k < self->V; k++) {
            eigen[k] = a[k]/normalized_value;
            a[k] = out_degrees[k] * eigen[k];
        }
    }
    

    free(a);
    free(out_degrees);
    
    return eigen;
}

// generates a random graph with topological preference and social bubbles
// you should NOT need to modify this function
Graph polly_generator(int n, float w) {
	Graph G;
	G.V = n*n;
	float* social = malloc(G.V * sizeof * social);
	float* economic = malloc(G.V * sizeof * economic);

	G.edges = malloc(G.V * sizeof * G.edges);
	float *popularity = malloc(G.V * sizeof * popularity);

	for (int i = 0; i < G.V; i++) {
		G.edges[i].head = NULL;
		social[i] = (float)rand() / (float)RAND_MAX;
		economic[i] = (float)rand() / (float)RAND_MAX;
	}

	for (int u = 0; u < G.V; u++) {
		for (int v = u + 1; v < G.V; v++) {
			int xu = u % n;
			int yu = u / n;
			int xv = v % n;
			int yv = v / n;

			float distance = sqrtf((xu - xv) * (xu - xv) + (yu - yv) * (yu - yv));
			float polly_dist = sqrtf((social[u] - social[v]) * (social[u] - social[v]) + (economic[u] - economic[v]) * (economic[u] - economic[v]));
			distance = distance * (1.0f + polly_dist);
			float prob = exp(-distance*distance/(w*w));
			if ((float)rand() / RAND_MAX < prob) {
				Edge e;

				e.to_vertex = v;
				e.weight = 0;
				insert_edge(&G.edges[u], e);

				e.to_vertex = u;
				e.weight = 0;
				insert_edge(&G.edges[v], e);
			}
		}
	}

	return G;
}

