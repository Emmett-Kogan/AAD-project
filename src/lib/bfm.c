#include "bfm.h"

int *BellmanFord(struct Graph *graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int *dist = (int *) malloc(sizeof(int)*V);

    // Initialize distance array
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Relaxing edges
    for (int i = 1; i <= V-1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;

            if (dist[u] != INT_MAX)
                dist[v] = MIN(dist[v], dist[u] + weight);
        }
    }

    // Checking for negative weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph->edges[i].src;
        int v = graph->edges[i].dest;
        int weight = graph->edges[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            ERREXIT("Negative edge?\n")
    }

    return dist;
}