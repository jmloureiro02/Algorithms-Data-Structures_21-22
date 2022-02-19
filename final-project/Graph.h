#ifndef GraphHeader
#define GraphHeader

typedef struct {unsigned int val; unsigned short L; unsigned short C;} ADJ;
typedef struct {int V; ADJ **adj;} Graph;

Graph *getEdges(Graph *G, int walls, int L, int C, int **map);

Graph *initGraph(int V);

void allocAdj(Graph *G);

void freeGraph(Graph *G);

#endif