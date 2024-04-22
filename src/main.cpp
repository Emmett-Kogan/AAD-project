#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "lib/bfm.h"

#include <bits/stdc++.h> 
#include <utility>
#include <unordered_map>

#define INFILE "grid.txt"
#define OUTFILE "pathLength.txt"
#define BUFFER_SIZE 32

struct Vector2 {
    int r, c;
};

struct Graph *convert(void);
void initEdge(struct Edge *e, struct Vector2 src, struct Vector2 dest);
void *BellmanFordWrapper(void *arg);

static struct Graph *g;
static int rows, cols;
static int **heights, **paths;

int main(int argc, char **argv) {
    // If in debug mode, take path as cmd line arg, otherwise assume ./grid.txt
    #ifdef DEBUG
    if (argc < 2)
        ERREXIT("Missing command line arg\n");

    // Open input file    
    FILE *fptr = fopen(argv[1], "r");
    #else
    FILE *fptr = fopen(INFILE, "r");
    #endif
    if (!fptr)
        ERREXIT("fopen failed\n");
    
    // Get grid size
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, fptr);

    // For the big test case, rows and cols was swapped around. Adding this to support it during testing
    #ifdef BIG
    cols = atoi(strtok(buffer, ","));
    rows = atoi(strtok(NULL, " "));
    #else
    rows = atoi(strtok(buffer, ","));
    cols = atoi(strtok(NULL, " "));
    #endif

    // Initializing heights array (grid graph)
    heights = (int **) calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++)
        heights[i] = (int *) calloc(cols, sizeof(int));

    while(fgets(buffer, BUFFER_SIZE, fptr)) {
        int count = 0;
        for (unsigned long i = 0; i < 32 && buffer[i] != '\0'; i++)
            if (buffer[i] == ',')
                count++;

        // If less than 2 commas, have to parse differenty as this is start and end coords
        if (count < 2)
            break;

        int height = atoi(strtok(buffer, ","));
        int row = atoi(strtok(NULL, ","));
        int col = atoi(strtok(NULL, " "));
        heights[row][col] = height;
    }

    // Parse src and dest coordinates
    struct Vector2 src;
    std::pair<int, int> B[8];
    int dest_count = 0;

    // Only ever 1 source node
    src.r = atoi(strtok(buffer, ","));
    src.c = atoi(strtok(NULL, " "));

    // Parse dest nodes in B until EOF (max 8 so maybe bounds check that too) 
    while(fgets(buffer, BUFFER_SIZE, fptr)) {
        B[dest_count].first = atoi(strtok(buffer, ","));
        B[dest_count].second = atoi(strtok(NULL, " "));
        if (dest_count++ == 8) break;
    }

    fclose(fptr);

    // Convert input node list to edge list (assuming grid matrix)
    g = convert();

    // Run Bellman Ford with each node in {src,  B} as the starting node
    pthread_t *threads = (pthread_t *) malloc(sizeof(pthread_t)*(1+dest_count));

    paths = (int **) malloc(sizeof(int *)*(1+dest_count));
    std::pair<int, int> args[9];    // doing it this way so I don't have to deal with any race conditions
    for (int i = 0; i < 1+dest_count; i++) {
        args[i] = std::make_pair(i, (i == 0) ? (src.r*cols + src.c) : (B[i-1].first*cols + B[i-1].second));
        pthread_create(&threads[i], NULL, BellmanFordWrapper, (void *) &args[i]);
    }

    void *res;
    for (int i = 0; i < 1+dest_count; i++)
        pthread_join(threads[i], &res);

    free(threads);

    // Map node numbers to position in B for paths indexing (is dependent on original order)
    std::unordered_map<int, int> lut;
    for (int i = 0; i < dest_count; i++)
        lut[B[i].first*cols+B[i].second] = i;

    sort(B, dest_count+B);

    // Calculate cost of each permutation and keep the best one
    int best_path_length = INT_MAX;
    do {
        // Get cost of permutation
        int path_length = paths[0][B[0].first*cols + B[0].second];
        for (int i = 1; i < dest_count; i++) 
           path_length += paths[1+lut[B[i-1].first*cols+B[i-1].second]][B[i].first*cols+B[i].second];

        // If smallest so far then update min
        best_path_length = MIN(best_path_length, path_length);
    } while(std::next_permutation(B, dest_count+B));

    // Write path length to output file
    fptr = fopen(OUTFILE, "w");
    fprintf(fptr, "%d", best_path_length);
    fclose(fptr);

    return 0;
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

void *BellmanFordWrapper(void *arg)
{
    std::pair<int, int> *args = (std::pair<int, int> *) arg;
    paths[args->first] = BellmanFord(g, args->second);
    pthread_exit(NULL);

    // Just so g++ hops off my back, this is never reachable
    return NULL;
}