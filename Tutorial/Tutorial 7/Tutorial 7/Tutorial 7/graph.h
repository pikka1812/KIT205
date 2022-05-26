//
//  graph.h
//  Tutorial 7
//
//  Created by Phong on 28/04/2022.
//

#ifndef graph_h
#define graph_h

typedef struct edge{
    int to_vertex;
    int weight;
} Edge;

typedef struct edgeNode{
    Edge edge;
    struct edgeNode *next;
} *EdgeNodePtr;

typedef struct edgeList{
    EdgeNodePtr head;
} EdgeList;

typedef struct graph{
    int V;
    EdgeList *edges;
} Graph;


#endif /* graph_h */
