#ifndef BFM_H
#define BFM_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#define MIN(a,b) ((a < b) ? a : b)
#define MAX(a,b) ((a > b) ? a : b)
#define COST(a,b) (MAX(-1, 1+(b-a)))
#define ERREXIT(s) { fprintf(stderr, s); exit(-1); }

// Based on GFG article on Bellman-Ford-Moore Algorithm
struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge *edges;     // graph is an array of edges
};

int *BellmanFord(struct Graph *graph, int src);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // BFM_H