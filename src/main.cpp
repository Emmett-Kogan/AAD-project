#include <cstddef>
#include <errno.h>
#include <iostream>

#include <string.h>
#include <stdio.h>

#include "bfm.h"



#define INFILE "grid.txt"
#define BUFFER_SIZE 32
#define ERREXIT(s) { fprintf(stderr, s); exit(-1); }

int countOccurences(char *str, char c, size_t length);

struct Vector2 {
    int r, c;
};

int main(int argc, char **argv) {
    // Open input file    
    FILE *fptr = fopen(INFILE, "r");
    if (!fptr)
        ERREXIT("fopen failed\n");

    // Get grid size
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, fptr);
    int rows = atoi(strtok(buffer, ",")), cols = atoi(strtok(NULL, " "));

    printf("Rows: %d\tCols: %d\n", rows, cols);

    // Initializing heights array (grid graph)
    int **heights = (int **) calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++)
        heights[i] = (int *) calloc(cols, sizeof(int));

    while(fgets(buffer, BUFFER_SIZE, fptr)) {
        // If less than 2 commas, have to parse differenty as this is start and end coords
        if (countOccurences(buffer, ',', BUFFER_SIZE) < 2)
            break;

        int height = atoi(strtok(buffer, ","));
        int row = atoi(strtok(NULL, ","));
        int col = atoi(strtok(NULL, " "));

        #ifdef DEBUG
        printf("(Height, Row, Col) = (%d, %d, %d)\n", height, row, col);
        #endif
    }

    Vector2 src, dest;

    src.r = atoi(strtok(buffer, ","));
    src.c = atoi(strtok(NULL, " "));

    fgets(buffer, BUFFER_SIZE, fptr);

    dest.r = atoi(strtok(buffer, ","));
    dest.c = atoi(strtok(NULL, " "));

    printf("Source:      (%d, %d)\n", src.r, src.c);
    printf("Destination: (%d, %d)\n", dest.r, dest.c);

    return 0;
}

int countOccurences(char *str, char c, size_t length) {
    int count = 0;
    for (unsigned long i = 0; i < length; i++)
        if (str[i] == c)
            count++;
        else if (str[i] == '\0')
            return count;
    return count;
}

    // struct Graph *graph = createGraph(atoi(argv[1]), atoi(argv[2]));

    // // add edge 0-1 (or A-B in above figure)
    // graph->edges[0].src = 0;
    // graph->edges[0].dest = 1;
    // graph->edges[0].weight = -1;

    // // add edge 0-2 (or A-C in above figure)
    // graph->edges[1].src = 0;
    // graph->edges[1].dest = 2;
    // graph->edges[1].weight = 4;

    // // add edge 1-2 (or B-C in above figure)
    // graph->edges[2].src = 1;
    // graph->edges[2].dest = 2;
    // graph->edges[2].weight = 3;

    // // add edge 1-3 (or B-D in above figure)
    // graph->edges[3].src = 1;
    // graph->edges[3].dest = 3;
    // graph->edges[3].weight = 2;

    // // add edge 1-4 (or B-E in above figure)
    // graph->edges[4].src = 1;
    // graph->edges[4].dest = 4;
    // graph->edges[4].weight = 2;

    // // add edge 3-2 (or D-C in above figure)
    // graph->edges[5].src = 3;
    // graph->edges[5].dest = 2;
    // graph->edges[5].weight = 5;

    // // add edge 3-1 (or D-B in above figure)
    // graph->edges[6].src = 3;
    // graph->edges[6].dest = 1;
    // graph->edges[6].weight = 1;

    // // add edge 4-3 (or E-D in above figure)
    // graph->edges[7].src = 4;
    // graph->edges[7].dest = 3;
    // graph->edges[7].weight = -3;
    
    //   // Function call
    // return BellmanFord(graph, 0);