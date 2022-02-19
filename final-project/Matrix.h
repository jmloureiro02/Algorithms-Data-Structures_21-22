#ifndef MatrixHeader
#define MatrixHeader

#include <stdio.h>
#include <stdbool.h>

#include "Graph.h"

void checkAlloc(void *ptr);

int BoundCheck(int **map,int l,int c,int maxl,int maxc);

void spread(int **array,int x1, int y1, int limX, int limY, int old, int New);

int findRooms(int **map, int L, int C);

int minDistance(int *dist, bool *sptSet, Graph *G);

void search(Graph *G, int startnode, int endnode, FILE *fout);

void freePyramid(int **pyr, int L);

void checkRooms(int L, int C, int maxL, int maxC, int **map, Graph *G);


#endif