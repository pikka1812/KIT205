#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// Displays a map of Ausqaurlia with voting prefences
// You should NOT modify this function
void show_voting_prefs(Graph* self, int* prefs, int quiet) {
	int p[3];
	p[0] = p[1] = p[2] = 0;

	int size = (int)sqrt(self->V);

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (prefs[y * size + x] == 0) {
				p[0]++; 
				if (!quiet)
					printf("<>");
			}
			else if (prefs[y * size + x] == 1) {
				p[1]++;
				if (!quiet)
					printf("::");
			}
			else {
				p[2]++;
				if (!quiet)
					printf("==");
			}
		}
		if (!quiet)
			printf("\n");
	}
	printf("  Red: %6d Green: %6d  Blue: %6d\n ", p[0], p[1], p[2]);
}

void step(Graph* self, int* prefs, float prob) {
    // create a new array called old_prefs
    // copy from prefs into old_prefs
    int *old_prefs = malloc(self->V * sizeof(int));
    for (int i = 0 ; i < self->V; i++) {
        old_prefs[i] = prefs[i];
    }
    
	// For each(undirected) edge(u->v) in the graph :
    for (int u = 0; u < self->V; u++) {
        EdgeNodePtr current = self->edges[u].head;
        int v;
        while(current != NULL) {
            v = current->edge.to_vertex;
            //   Generate a random number using :
            float chance = (float)rand() / (float)RAND_MAX;
            if(u < v) {
                if(chance < prob) {
                    if (rand()%2) {
                        prefs[u] = old_prefs[v];
                    }
                    else {
                        prefs[v] = old_prefs[u];
                    }
                }
            }
            current = current->next;
        }
    }
    free(old_prefs);
}


int main() {	
	//srand(time(NULL)); // can use this to pick a random seed
	srand(2021);         // but use seed = 2022 when you submit

	// Build Social Network
	Graph G;
	int size = 75;                  // can make this smaller for testing, but use 75 when you submit
	G = polly_generator(size, 4);   // a value smaller than 4 will give fewer edges, but use 4 when you submit
    
    
//    EdgeList test =  bfs(&G, 0);
//    EdgeNodePtr current = test.head;
//    while (current != NULL) {
//        printf("%d : %d \n", current->edge.to_vertex, current->edge.weight);
//        current = current->next;
//    }
//
//    for (int i = 0; i < G.V; i++) {
//        EdgeNodePtr current = G.edges[i].head;
//        printf("%d: ", i);
//        while(current != NULL) {
//            printf("to %d weight %d, ", current->edge.to_vertex, current->edge.weight);
//            current = current->next;
//        }
//        printf("\n");
//    }

	// Preference
	int* pref = malloc(G.V * sizeof *pref);

//	**************
//	** Before **
//	**************

	// Initialise population
	for (int i = 0; i < G.V; i++) {
		pref[i] = rand()%3;
	}

	// Run for 28 days
	printf("Before...\n");
	for (int i = 0; i < 28; i++) {
		step(&G, pref, 0.2);
		show_voting_prefs(&G, pref, 1);
	}
	show_voting_prefs(&G, pref,1);
	printf("\n");

//	******************
//	** Calculate centrality and sorted them based on the score**
//	******************

    double* scores = centrality(&G); // array of scores
    int* index = malloc(G.V * sizeof(int)); // index array that match with the score
    
    double temp; // helper variable for sorting
    int indexTemp; // helper variable for sorting
    
    //init the index array
    for (int i = 0; i < G.V ; i++) {
        index[i] = i;
    }
    
    //sorting the score array and index array based on the score
    for (int i = 0; i < G.V; i++) {
        for (int j = i+1; j < G.V; j++) {
            if (scores[i] < scores[j]) {
                temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
                
                indexTemp = index[i];
                index[i] = index[j];
                index[j] = indexTemp;
            }
        }
    }
    
//    ******************
//    ** After **
//    ******************
    
    // Run simulation for 28 more days
    printf("After...\n");
	for (int i = 0; i < 28; i++) {
        
        
        //Get the 10 people that have most influence and are not voting for team 1 and change their vote to team 1
        int a = 0, b = 0;
        while(a < 10) { // while not enough 10 people
            // loop through the sorted index array to find
            // because the index array is already sorted based on score so people at the first are always that have highest score
            while (b < G.V) {
                if (pref[index[b]] != 1) { // find a guy that is not voting for team 1
                    pref[index[b]] = 1; // change the vote
                    a++; // increase the number
                    b++;
                    break;
                }
                else {
                    b++;
                }
            }
        }
        
		step(&G, pref,0.2);
		show_voting_prefs(&G, pref,1);
	}
	show_voting_prefs(&G, pref,1);
	printf("\n");
    
    free(scores);
    free(index);

	return 0;
}
