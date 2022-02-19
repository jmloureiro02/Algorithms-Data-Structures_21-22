#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "Graph.h"
#include "Matrix.h"

void readPyramids(char *name,char *output);

/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * Returns: int status
 * Side-Effects: none
 *
 * Description: main Program
 *****************************************************************************/
int main (int argc, char **argv){
	char *name, *output;
	int size;
	if (argc == 2){
		size = strlen(argv[1]);
        if((name = (char*)calloc((size+1),sizeof(char))) == NULL) exit(0);
        if((output = (char*)calloc((size+2),sizeof(char))) == NULL) exit(0);
		strcpy(name,argv[1]);
		strncpy(output,name,size-3);
		strcat(output,".sol");
		readPyramids(name,output);
		free(name);
		free(output);
	} else exit(0);
	
	return 0;
}


/******************************************************************************
 * readPyramids()
 *
 * Arguments: name - pointer to file name's string
 *            output -  pointer to output name's string
 * Returns: void
 * Side-Effects: none
 *
 * Description: File reading function, includes input verification and prints value to the ouput file accordingly
 *****************************************************************************/
void readPyramids(char *name,char *output){
	FILE *fpin=NULL;
	FILE *fout = NULL;
	int L, C, targetL, targetC, walls, a, b, c, **pyr;
	Graph *G;
	int endroom;
    
	if((fpin = fopen(name,"r"))==NULL){
		free(name);
		free(output);
		exit(0);
	}
	if((fout = fopen(output,"w"))==NULL){
		free(name);
		free(output);
		exit(0);
	}

	while (fscanf(fpin, "%d %d", &L, &C) == 2){

		if((L > 0) && (C > 0)){
			pyr = (int **)malloc(L*sizeof(int*));
			checkAlloc(pyr);
			for (int i = 0; i < L; i++){
				pyr[i] = (int *)calloc(C, sizeof(int));
				checkAlloc(pyr[i]);
			}

			if (fscanf(fpin, "%d %d\n%d", &targetL, &targetC, &walls) != 3) exit(0);
			targetL--; targetC--;
			for (int i = 0; i < walls; i++){
				if (fscanf(fpin, "%d %d %d", &a, &b, &c) != 3) exit(0);
				pyr[a-1][b-1] = c;
			}
			if( BoundCheck(pyr,targetL,targetC,L-1,C-1) == 1){
				if(pyr[targetL][targetC] != 0){
					fprintf(fout,"-1\n\n");
					freePyramid(pyr,L);
					continue;
				}
				G = initGraph(findRooms(pyr, L, C));
				endroom = (pyr[targetL][targetC] + 2) * (-1);
				G = getEdges(G,walls,L,C,pyr);
				search(G,0,endroom,fout);
				freeGraph(G);
			} else {
				fprintf(fout,"-1\n\n");
				freePyramid(pyr,L);
			}

		} else {
			if (fscanf(fpin, "%d %d\n%d", &targetL, &targetC, &walls) != 3) exit(0);
			for (int i = 0; i < walls; i++)
				if (fscanf(fpin, "%d %d %d", &a, &b, &c) != 3) exit(0);
			fprintf(fout,"-1\n\n");
		}
	}

	fclose(fpin);
	fclose(fout);
}
