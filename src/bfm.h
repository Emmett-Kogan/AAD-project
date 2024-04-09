#ifndef BFM_H
#define BFM_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdlib.h>

// Based on GFG article on Bellman-Ford-Moore Algorithm
struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge *edges;     // graph is an array of edges
};

struct Graph *createGraph(int V, int E);
void BellmanFord(struct Graph *graph, int src);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // BFM_H