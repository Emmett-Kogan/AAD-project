#include <string.h>
#include <stdio.h>
#include "lib/bfm.h"

#define INFILE "grid.txt"
#define OUTFILE "pathLength.txt"
#define BUFFER_SIZE 32

struct Vector2 {
    int r, c;
};

int countOccurences(char *str, char c, size_t length);
struct Graph *convert(void);
void initEdge(struct Edge *e, struct Vector2 src, struct Vector2 dest);
int opt(int **paths, struct Vector2 *B, int b_len);
int opt_rec(int **paths, struct Vector2 *B, int b_len, int path_length);

static int rows, cols;
static int **heights;

int main(int argc, char **argv) {
    if (argc < 2)
        ERREXIT("Missing command line arg\n");

    // Open input file    
    FILE *fptr = fopen(argv[1], "r");
    if (!fptr)
        ERREXIT("fopen failed\n");

    // Get grid size
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, fptr);
    rows = atoi(strtok(buffer, ","));
    cols = atoi(strtok(NULL, " "));

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
        heights[row][col] = height;
    }

    // Parse src and dest coordinates
    struct Vector2 src, B[8];
    int dest_count = 0;

    // Only ever 1 source node
    src.r = atoi(strtok(buffer, ","));
    src.c = atoi(strtok(NULL, " "));

    // Parse dest nodes in B until EOF (max 8 so maybe bounds check that too) 
    while(fgets(buffer, BUFFER_SIZE, fptr)) {
        B[dest_count].r = atoi(strtok(buffer, ","));
        B[dest_count].c = atoi(strtok(NULL, " "));
        if (dest_count++ == 8) break;
    }

    fclose(fptr);

    // Convert input node list to edge list (assuming grid matrix)
    struct Graph *g = convert();

    // Get shortest paths to each node from the source node and each node in B
    int index = 0, **paths = (int **) malloc(sizeof(int *)*(1+dest_count));
    paths[index++] = BellmanFord(g, src.r*cols + src.c);

    for (int i = 0; i < dest_count; i++)
        paths[1+i] = BellmanFord(g, B[i].r*cols + B[i].c);

    #ifdef DEBUG
    printf("\nS: (%d, %d)\n", src.r, src.c);
    for (int i = 0; i < dest_count; i++)
        printf("%d: (%d, %d) -- %d\n", i, B[i].r, B[i].c, paths[0][B[i].r*cols + B[i].c]);
    #endif

    // Now I need to find the best permutation given the paths...
    int path_length = opt(paths, B, dest_count);

    // Write path length to output file
    // fptr = fopen(OUTFILE, "w+");
    // fprintf(fptr, "%d\n", pathLength);
    // fclose(fptr);

    return 0;
}

int countOccurences(char *str, char c, size_t length) 
{
    int count = 0;
    for (unsigned long i = 0; i < length && str[i] != '\0'; i++)
        if (str[i] == c)
            count++;
    return count;
}

struct Graph *convert(void) 
{
    // Construct edge list of graph :)
    int num_edges = ((2*rows*cols) - rows - cols) * 2;  // note unidirecitonal graph
    struct Graph *g = (struct Graph *) malloc(sizeof(struct Graph));
    g->V = rows*cols;
    g->E = num_edges;
    g->edges = (struct Edge *) malloc(sizeof(struct Edge)*num_edges);

    int index = 0;
    struct Vector2 src, dest;

    // For each node (where node number = rows*cols + col)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Init src vec2
            src.r = i; src.c = j;

            // conditionally add top edge
            if (i > 0) {
                dest.r = i-1; dest.c = j;
                initEdge(&g->edges[index++], src, dest);
            }
            // conditionally add bottom edge
            if (i < rows-1) {
                dest.r = i+1; dest.c = j;
                initEdge(&g->edges[index++], src, dest);             
            }
            // conditionally add left edge
            if (j > 0) {
                dest.r = i; dest.c = j-1;
                initEdge(&g->edges[index++], src, dest);
            }
            // conditionally add right edge
            if (j < cols-1) {
                dest.r = i; dest.c = j+1;
                initEdge(&g->edges[index++], src, dest);
            }
        }
    }

    return g;
}

void initEdge(struct Edge *e, struct Vector2 src, struct Vector2 dest) 
{
    e->src = src.r*cols + src.c;
    e->dest = dest.r*cols + dest.c;
    e->weight = COST(heights[src.r][src.c], heights[dest.r][dest.c]);
}

// This function takes in the array of paths to each node for src and all of the nodes in B
// Now the first thing that happens is that src goes to any node in B, and then any node in B to any other node in B
// This might need to be a wrapper function since src is a special case, or I could do a 
// static int depth and do something based off that
/*
    So what would be best is a recursive function, that checks all of them
    So the first level would be, for each node in B, call the alg again with path length
    and a version of B that no longer includes the node it is being called on (could repalce
    with special value, but using a set would probably be easiest)
    So in each recursive call, I set a temp variable equal to the thing I'm about to call on,
    Then remove that from the set being passed in
    And when I return I add it back in or something
    and the return value should be the path length I guess
 */

int opt(int **paths, struct Vector2 *B, int b_len)
{
    int *lengths = (int *) malloc(sizeof(int)*b_len);
    // I don't know how for each will work if I'm removing and adding nodes to the set a bunch









    return 0;
}

int opt_rec(int **paths, struct Vector2 *B, int b_len, int length)
{


    return 0;
}