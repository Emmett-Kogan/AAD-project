#include <cstddef>
#include <errno.h>
#include <iostream>

#include <string.h>
#include <stdio.h>

#include "bfm.h"



#define INFILE "grid.txt"
#define OUTFILE "pathLength.txt"

#define BUFFER_SIZE 32
#define ERREXIT(s) { fprintf(stderr, s); exit(-1); }



struct Vector2 {
    int r, c;
};

int countOccurences(char *str, char c, size_t length);
int getPathLength(int **graph, int rows, int cols, Vector2 src, Vector2 dest);  // each is 8 bytes which is the same size as a pointer
int getWeight(Vector2 src, Vector2 dest);

int main(int argc, char **argv) {
    // Open input file    
    FILE *fptr = fopen(INFILE, "r");
    if (!fptr)
        ERREXIT("fopen failed\n");

    // Get grid size
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, fptr);
    int rows = atoi(strtok(buffer, ",")), cols = atoi(strtok(NULL, " "));

    #ifdef DEBUG 
    printf("Rows: %d\tCols: %d\n", rows, cols);
    #endif

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
        heights[row][col] = height; // this can be improved

        #ifdef DEBUG
        printf("(Height, Row, Col) = (%d, %d, %d)\n", height, row, col);
        #endif
    }

    // Parse src and dest coordinates
    Vector2 src, dest;

    src.r = atoi(strtok(buffer, ","));
    src.c = atoi(strtok(NULL, " "));

    fgets(buffer, BUFFER_SIZE, fptr);

    dest.r = atoi(strtok(buffer, ","));
    dest.c = atoi(strtok(NULL, " "));

    // Close input file as we are done reading it
    fclose(fptr);

    #ifdef DEBUG
    printf("Source:      (%d, %d)\n", src.r, src.c);
    printf("Destination: (%d, %d)\n", dest.r, dest.c);
    #endif

    int pathLength = getPathLength(heights, rows, cols, src, dest);

    // Write path length to output file
    fptr = fopen(OUTFILE, "w+");
    fprintf(fptr, "%d\n", pathLength);
    fclose(fptr);

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

int getPathLength(int **graph, int rows, int cols, Vector2 src, Vector2 dest) {
    // Construct edge list of graph :)
    int num_edges = (2*rows*cols) - rows - cols;
    Edge *edges = (Edge *) malloc(sizeof(Edge)*num_edges);

    // I think I'm just going to convert the graph input into an edge list and then pass
    // that into the GFG bellman-ford implementation and then just print the thing...

    // an edge is a src node, dest node, and weight
    int index = 0;

    // top row
    // bottom row

    // sides

    // middle



    for (int i = 1; i < rows-1; i++) {
        for (int j = 1; j < cols-1; j++) {
            weights[index++] = COST
        }
    }

    printf("index: %d\n", index);

}

int getWeight(Vector2 src, Vector2 dest) {
    return MAX(-1, 1+)


}