#include <errno.h>
#include "bfm.h"


int main(int argc, char **argv) {
    if (argc < 2)
        return -EINVAL;

    struct Graph *graph = createGraph(atoi(argv[1]), atoi(argv[2]));

    // add edge 0-1 (or A-B in above figure)
    graph->edges[0].src = 0;
    graph->edges[0].dest = 1;
    graph->edges[0].weight = -1;

    // add edge 0-2 (or A-C in above figure)
    graph->edges[1].src = 0;
    graph->edges[1].dest = 2;
    graph->edges[1].weight = 4;

    // add edge 1-2 (or B-C in above figure)
    graph->edges[2].src = 1;
    graph->edges[2].dest = 2;
    graph->edges[2].weight = 3;

    // add edge 1-3 (or B-D in above figure)
    graph->edges[3].src = 1;
    graph->edges[3].dest = 3;
    graph->edges[3].weight = 2;

    // add edge 1-4 (or B-E in above figure)
    graph->edges[4].src = 1;
    graph->edges[4].dest = 4;
    graph->edges[4].weight = 2;

    // add edge 3-2 (or D-C in above figure)
    graph->edges[5].src = 3;
    graph->edges[5].dest = 2;
    graph->edges[5].weight = 5;

    // add edge 3-1 (or D-B in above figure)
    graph->edges[6].src = 3;
    graph->edges[6].dest = 1;
    graph->edges[6].weight = 1;

    // add edge 4-3 (or E-D in above figure)
    graph->edges[7].src = 4;
    graph->edges[7].dest = 3;
    graph->edges[7].weight = -3;
    
      // Function call
    return BellmanFord(graph, 0);
}