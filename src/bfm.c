#include "bfm.h"

struct Graph *createGraph(int V, int E) 
{
    struct Graph *g = (struct Graph *) malloc(sizeof(struct Graph));
    g->V = V;
    g->E = E;
    g->edges = (struct Edge *) malloc(sizeof(struct Edge)*E);
    return g;
}

void BellmanFord(struct Graph *graph, int src)
{
    int V = graph->V;
    int E = graph->E;
}