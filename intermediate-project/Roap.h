#ifndef __Roap__
#define __Roap__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

#define MAX_I 1E6

int a1(short **array,int x, int y,int size_x,int size_y);
int a2(short **array,int x, int y,int size_x,int size_y);
int a3(short **array,int x, int y,int size_x,int size_y);
int a4(short **array,int x, int y,int size_x,int size_y);
int a5(short **array,int x, int y,int size_x,int size_y);
int a6(short **array,int x1, int y1,int x2,int y2, int limX, int limY);
void ficheiro(char **name, char **output,int size);
void filewrite(short **array,int x1, int y1, int x2, int y2,int max_x,int max_y,char *mode,FILE *fout);
void arguments(int argc,char **argv,char **name,char **output,int *size);

#endif
