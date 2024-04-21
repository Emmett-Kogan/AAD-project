
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
struct Graph *convert(int **graph, int rows, int cols);
void initEdge(struct Edge *e, struct Vector2 src, struct Vector2 dest);

static int rows, cols;
static int **heights;

int main(int argc, char **argv) {
    // Open input file    
    FILE *fptr = fopen(INFILE, "r");
    if (!fptr)
        ERREXIT("fopen failed\n");

    // Get grid size
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, fptr);
    rows = atoi(strtok(buffer, ","));
    cols = atoi(strtok(NULL, " "));

    #ifdef DEBUG 
    printf("Rows: %d\tCols: %d\n", rows, cols);
    printf("(Height, Row, Col) -- node number\n");
    #endif

    // Initializing heights array (grid graph)
    heights = (int **) calloc(rows, sizeof(int *));
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
        printf("(%d, %d, %d) -- %d\n", height, row, col, row*cols + col);
        #endif
    }

    // Parse src and dest coordinates
    struct Vector2 src, dest;

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

    struct Graph *g = convert(heights, rows, cols);

    // Write path length to output file
    fptr = fopen(OUTFILE, "w+");
    // fprintf(fptr, "%d\n", pathLength);
    fclose(fptr);

    return 0;
}

int countOccurences(char *str, char c, size_t length) 
{
    int count = 0;
    for (unsigned long i = 0; i < length; i++)
        if (str[i] == c)
            count++;
        else if (str[i] == '\0')
            return count;
    return count;
}

struct Graph *convert(int **heights, int rows, int cols) 
{
    // Construct edge list of graph :)
    int num_edges = ((2*rows*cols) - rows - cols) * 2;  // note unidirecitonal graph
    struct Graph g = {
        .V = rows*cols,
        .E = num_edges,
        .edges = (struct Edge *) malloc(sizeof(struct Edge)*num_edges),
    };

    #ifdef DEBUG
    printf("Num edges: %d\n", num_edges);
    #endif

    struct Edge tmp;
    struct Vector2 src = { 
        .r = 0, 
        .c = 0
    };
    struct Vector2 dest = {
        .r = 0,
        .c = 1
    };
    initEdge(&tmp, src, dest);
    initEdge(&tmp, dest, src);



    // int index = 0;
    // Vector2 src, dest;
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         src = { .r = i, .c = j };

    //         // If corner

    //         if (i == 0 && j == 0) {
    //             edges[index] = {
    //                 .src = i*rows + cols,
    //                 .dest = ,
    //                 .weight = ,
    //             }
    //         } else if (i == 0 && j == cols-1) {

    //         } else if (i == rows-1 && j == 0) {

    //         } else if (i == rows-1 && j == cols-1) {

    //         }

    //         // If just side
    //         if (i == 0) {

    //         } else if (j == 0) {
 
    //         } else if (i == rows-1) {

    //         } else if (i == cols-1) {

    //         } else {
    //             // Middle node case

    //         }





    //     }
    // }


    // top row
    // bottom row

    // sides

    // middle
    return NULL;
}

void initEdge(struct Edge *e, struct Vector2 src, struct Vector2 dest) 
{
    printf("src:  (%d, %d, %d)\n", heights[src.r][src.c], src.r, src.c);
    printf("dest: (%d, %d, %d)\n", heights[dest.r][dest.c], dest.r, dest.c);

    int tmp = COST(heights[src.r][src.c], heights[dest.r][dest.c]);
    printf("cost of edge: %d\n", tmp);

    e->src = src.r*cols + src.c;
    e->dest = dest.r*cols + dest.c;
    e->weight = tmp;

    printf("Edge: (%d, %d, %d)\n", e->src, e->dest, e->weight);
    // need to convert from (r,c) to node number
    // also need to 


}