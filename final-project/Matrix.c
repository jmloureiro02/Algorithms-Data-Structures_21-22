#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "Graph.h"

/******************************************************************************
 * checkAlloc()
 *
 * Arguments: ptr - void pointer to allocated memory
 * Returns: void
 * Side-Effects: none
 *
 * Description: checks if the memory allocation was successful
 *****************************************************************************/

void checkAlloc(void *ptr){
	if (ptr == NULL) exit(0);
}

/******************************************************************************
 * BoundCheck()
 *
 * Arguments: array - pointer to 2 dimensional table that represents the pyramids "map"
 *            l - line coordinate
 * 			  c - column coordinate
 * 			  maxl - maximum line number
 * 			  maxc - maximum column number
 * Returns: interger where 1 represents true and 0 represents false statement
 * Side-Effects: none
 *
 * Description: function that checks if the statement "is (l,c) within the boundary of the 2D array map?" is true or false
 *****************************************************************************/

int BoundCheck(int **map,int l,int c,int maxl,int maxc){
	if(l < 0 || c < 0 || l > maxl || c > maxc) return 0;
	return 1;
}


/******************************************************************************
 * spread()
 *
 * Arguments: array - pointer to 2 dimensional table that represents the pyramids "map"
 *            x1 - x coordinate of origin
 * 	      y1 - y coordinate of origin
 *     	      limX - max value of x
 * 	      limY - max value of y
 * 	      old - value to be replaced
 * 	      new - value to replace with
 * Returns: void
 * Side-Effects: none
 *
 * Description: function that replaces an old value by a new one by spreading that new value to elements containing the old value
 *****************************************************************************/

void spread(int **array,int x1, int y1, int limX, int limY, int old, int New){
    int flag = 1;
	int i = 0;
    
    array[x1][y1] = New;

    while(flag == 1){
        flag = 0;
        for(int x = x1-i; x <= x1+i; x++){
            for(int y = y1-i; y <= y1+i; y++){
                if((x>=0) && (y>=0) && (x < limX) && (y < limY)){
					if (array[x][y] == New){
						if ((x+1 >= 0) && (x+1 < limX) && (y >= 0) && (y < limY)){
							if (array[x+1][y] == old){
								array[x+1][y] = New;
								flag = 1;
							}
						}
						if ((x-1 >= 0) && (x-1 < limX) && (y >= 0) && (y < limY)){
							if (array[x-1][y] == old){
								array[x-1][y] = New;
								flag = 1;
							}
						}
						if ((x >= 0) && (x < limX) && (y-1 >= 0) && (y-1 < limY)){
							if (array[x][y-1] == old){
								array[x][y-1] = New;
								flag = 1;
							}
						}
						if ((x >= 0) && (x < limX) && (y+1 >= 0) && (y+1 < limY)){
							if (array[x][y+1] == old){
								array[x][y+1] = New;
								flag = 1;
							}
						}
					}  
            	}
        	}
    	}
		i++;
	}
}


/******************************************************************************
 * findRooms()
 *
 * Arguments: array - pointer to 2 dimensional table that represents the pyramids "map"
 *            L -  number of lines
 * 			  C - number of columns
 * Returns: interger that represents the room number (starting with room number 1)
 * Side-Effects: none
 *
 * Description: function that divides empty spaces (value 0) into different rooms by atributing a value to them, starting with -2, -3, -4...
 *****************************************************************************/

int findRooms(int **map, int L, int C){
	int top, left;
	int roomNr = -2;
	int swapfrom, swapto;

	for (int i = 0; i < L; i++){
		for (int j = 0; j < C; j++){
			if (i == 0) {
				if (j == 0) map[i][j] = roomNr;
				else {
					if (map[i][j] == 0){
						if (map[i][j-1] < -1) map[i][j] = map[i][j-1];
						else {map[i][j] = --roomNr;} //decrementa na primeira linha quando tem parede atrÃ¡s
					}

				}
			}
			else {
				top = 0; left = 0;
				if (j == 0){
					if (map[i][j] == 0){
						if (map[i-1][j] < -1) {
							map[i][j] = map[i-1][j];
						} else map[i][j] = --roomNr; //decrementa quando estÃ¡ no inicio da linha e tem parede em cima
					}
				} else {
					if (map[i][j] == 0){
						if (map[i-1][j] < -1) top = map[i-1][j];
						if (map[i][j-1] < -1) left = map[i][j-1];
						if (top == 0){
							if (left == 0) map[i][j] = --roomNr; //decrementa quando tem parede em cima e atrÃ¡s
							else if (left < -1) map[i][j] = left;
						} else {
							if (top == left) map[i][j] = top;
							else if (left == 0) {
								map[i][j] = top;
							}
							else {
								if (top > left) {swapfrom = left; swapto = top;}
								else {swapfrom = top; swapto = left;} //realiza troca
								spread(map, i, j, L, C, swapfrom, swapto);
								roomNr++;
							}
						}

					}
				}
			}
		}
	}
	return (roomNr+1)*(-1);
}


/******************************************************************************
 * minDistance()
 *
 * Arguments: G - pointer to Graph struct
 * 			  dist -
 *            sptSet - 
 * Returns: interger that
 * Side-Effects: none
 *
 * Description: computes the minimum distance between two nodes ------------------------------------------------------------
 *****************************************************************************/

int minDistance(int *dist, bool *sptSet, Graph *G){
    int min = INT_MAX, min_index = 0;

    for (int v = 0; v < G->V; v++)
        if (sptSet[v] == false && dist[v] <= min) min = dist[v], min_index = v;

    return min_index;
}

/******************************************************************************
 * search()
 *
 * Arguments: G - pointer to Graph struct
 * 			  startnode - starting node
 *			  endnode - end node
 *            fout - pointer to output file
 * Returns: void
 * Side-Effects: none
 *
 * Description: finds the shortest path to the endroom (room that has the finish coordinates) node of the adjacency matrix, using Dijkstra's algorithm
 *****************************************************************************/

void search(Graph *G, int startnode, int endnode, FILE *fout){

    int *dist = calloc(G->V,sizeof(int));
	checkAlloc(dist);
    unsigned short *pred = calloc(G->V,sizeof(unsigned short));
	checkAlloc(pred);
	
    bool *visited = calloc(G->V,sizeof(bool));
	checkAlloc(visited);
	int u;
	

    for (int p = 0; p < G ->V; p++){
        dist[p] = INT_MAX, visited[p] = false;
    }
    pred[0]=0;
    dist[0]=0;
    int count=1;

	for (count = 0; count < G->V - 1; count++)
	{
		u = minDistance(dist, visited, G);
		visited[u] = true;
		for (int v = 0; v < G->V; v++)
			if (!visited[v] && G->adj[u][v].val && dist[u] + G->adj[u][v].val < dist[v])
			{
				pred[v] = u;
				dist[v] = dist[u] + G->adj[u][v].val;
			} 
	}
	free(visited);
	
	unsigned short *path = calloc(G->V,sizeof(unsigned short));
	checkAlloc(path);

    if (dist[endnode] != INT_MAX){
		fprintf(fout,"%d\n", dist[endnode]);
		if (dist[endnode] != 0){
			int i = 0; int count = 0;
			int j = endnode;
			path[i] = j;
			do {
				j = pred[j];
				path[++i] = j;
				count++;
			} while(j != startnode);
			fprintf(fout,"%d\n", count);
			for (i = count; i > 0; i--){
				fprintf(fout,"%d %d %d\n", G->adj[path[i]][path[i-1]].L+1, G->adj[path[i]][path[i-1]].C+1, G->adj[path[i]][path[i-1]].val);
			}
		}
		fprintf(fout,"\n");
	} else fprintf(fout, "-1\n");
	free(dist);
	free(pred);
	free(path);
	
	
}


/******************************************************************************
 * freePyramid()
 *
 * Arguments: pyr - pointer to 2D table representing the pyramid's "map"
 * 			  L - maximum line number
 * Returns: void
 * Side-Effects: none
 *
 * Description: frees allocated memory for the pyramid map's matrix
 *****************************************************************************/

void freePyramid(int **pyr, int L){
	for (int i = L-1; i >= 0; i--) free(pyr[i]);
	free(pyr);
}


/******************************************************************************
 * checkRooms()
 *
 * Arguments: L - line coordinate
 * 			  C - column coordinate
 * 			  maxL - maximum line number
 *            maxC - maximum column number
 * 		      map - pointer to 2D table representing the pyramid's "map"
 * 			  G - pointer to Graph struct
 * Returns: void
 * Side-Effects: none
 *
 * Description: checks if the coordinates corresponds to a breakable wall between 2 rooms and fills the adjacency matrix with the corresponding minimum cost wall
 *****************************************************************************/

void checkRooms(int L, int C, int maxL, int maxC, int **map, Graph *G){
	int vertex1; int vertex2;

	if (L-1 >= 0 && L+1 < maxL){
		if ((map[L-1][C] < -1) && (map[L+1][C] < -1) && (map[L-1][C] != map[L+1][C])){
			vertex1 = (map[L-1][C] + 2) * (-1);
			vertex2 = (map[L+1][C] + 2) * (-1);
			if (G->adj[vertex1][vertex2].val == 0) {
				G->adj[vertex1][vertex2].val = map[L][C];
				G->adj[vertex2][vertex1].val = map[L][C];
				G->adj[vertex1][vertex2].L = L;
				G->adj[vertex2][vertex1].L = L;
				G->adj[vertex1][vertex2].C = C;
				G->adj[vertex2][vertex1].C = C;
			}
			else {
				if ( map[L][C] < G->adj[vertex1][vertex2].val ){
					G->adj[vertex1][vertex2].val = map[L][C];
					G->adj[vertex2][vertex1].val = map[L][C];
					G->adj[vertex1][vertex2].L = L;
					G->adj[vertex2][vertex1].L = L;
					G->adj[vertex1][vertex2].C = C;
					G->adj[vertex2][vertex1].C = C;
				}
			}
		}
	}
	if (C-1 >= 0 && C+1 < maxC){
		if ((map[L][C-1] < -1) && (map[L][C+1] < -1) && (map[L][C-1] != map[L][C+1])){
			vertex1 = (map[L][C-1] + 2) * (-1);
			vertex2 = (map[L][C+1] + 2) * (-1);
			if (G->adj[vertex1][vertex2].val == 0) {
				G->adj[vertex1][vertex2].val = map[L][C];
				G->adj[vertex2][vertex1].val = map[L][C];
				G->adj[vertex1][vertex2].L = L;
				G->adj[vertex2][vertex1].L = L;
				G->adj[vertex1][vertex2].C = C;
				G->adj[vertex2][vertex1].C = C;
			}
			else {
				if ( map[L][C] < G->adj[vertex1][vertex2].val ){
					G->adj[vertex1][vertex2].val = map[L][C];
					G->adj[vertex2][vertex1].val = map[L][C];
					G->adj[vertex1][vertex2].L = L;
					G->adj[vertex2][vertex1].L = L;
					G->adj[vertex1][vertex2].C = C;
					G->adj[vertex2][vertex1].C = C;
				}
			}
		}
	}
}

