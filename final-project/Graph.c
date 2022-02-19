#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "Matrix.h"

/******************************************************************************
 * freeGraph()
 *
 * Arguments: G - pointer to Graph struct
 * Returns: void
 * Side-Effects: nonee
 *
 * Description: frees memory allocated for the adjacency matrix
 *****************************************************************************/

void freeGraph(Graph *G){
	for (int i = G->V-1; i >= 0; i--) free(G->adj[i]);
	free(G->adj);
	free(G);
}


/******************************************************************************
 * allocAdj()
 *
 * Arguments: G - pointer to Graph structt
 * Returns: void
 * Side-Effects: none
 *
 * Description: allocates memory for the graph's adjacency matrix
 *****************************************************************************/

void allocAdj(Graph *G){
	G->adj = (ADJ **)malloc(G->V*sizeof(ADJ *));
	checkAlloc(G->adj);
	for (int i = 0; i < G->V; i++){
		G->adj[i] = (ADJ *)calloc(G->V, sizeof(ADJ));
		checkAlloc(G->adj[i]);
	}
}

/******************************************************************************
 * getEdges()
 *
 * Arguments: G - pointer to Graph struct
 * 			  walls - number of walls
 * 			  L - maximum number of lines
 * 			  C - maximum number of columns
 * 		      map - pointer to 2D table representing the pyramid's "map"
 * Returns: pointer to Graph struct
 * Side-Effects: none
 *
 * Description: goes through the matrix and retrieves the breakabÃ§e wall of minimum cost between 2 rooms
 *****************************************************************************/

Graph *getEdges(Graph *G, int walls, int L, int C, int **map){

	for (int i = 0; i < L; i++){
		for (int j = 0; j < C; j++){
			if (map[i][j] > 0) checkRooms(i, j, L, C, map, G);
		}
	}
	freePyramid(map, L);
	return G;
	
}

/******************************************************************************
 * initGraph()
 *
 * Arguments: V - number of nodes
 * Returns: pointer to Graph struct
 * Side-Effects: none
 *
 * Description: allocates Graph strucf and adjacency matrix
 *****************************************************************************/

Graph *initGraph(int V){
	Graph *G;
	G = (Graph *)malloc(sizeof(Graph));
	checkAlloc(G);
	G->V = V;
	allocAdj(G);
	return G;
}