#include "Roap.h"


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

int main(int argc, char **argv){
    char *name = NULL, *output=NULL;
    int size;
    arguments(argc,argv,&name,&output,&size);
    ficheiro(&name,&output,size);
    return 0;
}


/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 *            name - pointer to file name's string
 *            ouput -  pointer to altered "name" string
 *            size - (number of carachters + 1) of "name" string
 * Returns: int status
 * Side-Effects: none
 *
 * Description: main Program
 *****************************************************************************/

void arguments(int argc, char **argv,char **name, char **output,int *size){
    char opt;
    while ( (opt = getopt(argc, argv, "s:")) != -1 )
    {
        switch(opt)
        {
            case 's':
                *size = strlen(optarg);
                if((*name = (char*)calloc((*size+1),sizeof(char))) == NULL) exit(0);
                if((*output = (char*)calloc((*size+2),sizeof(char))) == NULL) exit(0);
                strcpy(*name,optarg);
                break;
        }
    }
}


/******************************************************************************
 * ficheiro ()
 *
 * Arguments: name - pointer to file name's string
 *            ouput -  pointer to altered "name" string
 *            size - number of characters (including null) of "name" string
 * Returns: void
 * Side-Effects: none
 *
 * Description: File reading function
 *****************************************************************************/

void ficheiro(char **name, char **output,int size){
    int f_flag,token1,token2,token3,board_x,board_y,finish_x,finish_y,num_obstacles, x2=0,y2=0;
    char mode[4];
    FILE *fpin=NULL, *fpout=NULL;

    if((fpin = fopen(*name,"r"))==NULL)exit(0);
    strncpy(*output,*name,size-4);
    if((fpout = fopen(strcat(*output,".sol1"),"w"))==NULL)exit(0);
    
    while(fscanf(fpin,"%d %d",&board_x,&board_y)==2){
    
        short** arr = (short**)calloc((board_x),sizeof(short*));
        for (int i = 0; i < board_x; i++) arr[i] = (short*)calloc((board_y),sizeof(short));

        if(fscanf(fpin,"%d %d %s",&finish_x,&finish_y,mode)!=3)exit(0);
        if(mode[1]=='6'){
            if(fscanf(fpin,"%d %d",&x2,&y2)!=2) exit(0);
        }

        if(fscanf(fpin,"%d",&num_obstacles)!=1)exit(0);

        for(int i = 0; i < num_obstacles; i++){
            if((f_flag = fscanf(fpin,"%d %d %d",&token1,&token2,&token3))==EOF)
                exit(0);
            arr[token1-1][token2-1] = token3;
        }

        filewrite(arr,finish_x,finish_y,x2,y2,board_x,board_y,mode,fpout);
        
        for (int a= 0; a < board_x; a++) free(arr[a]);
        free(arr);
    
    }
    free(*name);
    free(*output);
    fclose(fpin);
    fclose(fpout);
}


/******************************************************************************
 * filewrite ()
 *
 * Arguments: array - table data struct
 *            x1 - x coordinate of target element of the table structure
 *            y1 - y coordinate of target element of the table structure
 *            x2 - x coordinate of second target of the table structure (in case of mode 6)
 *            y2 - y coordinate of second target of the table structure (in case of mode 6)
 *            max_x - max x coordinate of the table structure
 *            max_y - max y coordinate of the table structure
 *            mode - string indicating mode
 *            fout - output file pointer
 *            ouput -  pointer to string containing output file name
 * Returns: void
 * Side-Effects: none
 *
 * Description: Selects which mode it executes based on the data given by
 *              the input file.
 *****************************************************************************/

void filewrite(short **array,int x1, int y1, int x2, int y2,int max_x,int max_y,char *mode,FILE *fout){
    switch (mode[1])
        {
            case '1':
                fprintf(fout,"%d\n\n",a1(array,x1,y1,max_x,max_y));//
                break;
            case '2':
                fprintf(fout,"%d\n\n",a2(array,x1,y1,max_x,max_y));
                break;
            case '3':
                fprintf(fout,"%d\n\n",a3(array,x1,y1,max_x,max_y));
                break;
            case '4':
                fprintf(fout,"%d\n\n",a4(array,x1,y1,max_x,max_y));
                break;
            case '5':
                fprintf(fout,"%d\n\n",a5(array,x1,y1,max_x,max_y));
                break;
            case '6':
                fprintf(fout,"%d\n\n",a6(array,x1,y1,x2,y2,max_x,max_y));
                break;
        }
}

/******************************************************************************
 * a1()
 *
 * Arguments: array - table data structure
 *            x - x coordinate of target element of the table structure
 *            y - y coordinate of target element of the table structure
 *            size_x - max x coordinate of the table structure
 *            size_y - max y coordinate of the table structure
 * Returns: integer based on the value of the element
 * Side-Effects: none
 *
 * Description: Executes mode a1
 *****************************************************************************/
int a1(short **array,int x, int y,int size_x,int size_y){
    int value;
    if( (x < 1) || (x > size_x) || (y > size_y) || (y < 1)) return -2;
    if(array[x-1][y-1] == -1) return 0;
    if((value = array[x-1][y-1]) >= 0) return value;
    else exit(0);
}

/******************************************************************************
 * a2()
 *
 * Arguments: array - table data structure
 *            x - x coordinate of target element of the table structure
 *            y - y coordinate of target element of the table structure
 *            size_x - max x coordinate of the table structure
 *            size_y - max y coordinate of the table structure
 * Returns: integer based on the value of nearby table elements
 * Side-Effects: none
 *
 * Description: Executes mode a2
 *****************************************************************************/
int a2(short **array,int x, int y,int size_x,int size_y){

	if( (x < 1) || (x > size_x) || (y > size_y) || (y < 1)) return -2;
    x--; y--;

	for (int i = x-1; i <= x+1; i+=2){
        if ((i >= 0) && (i < size_x)){
            if ( array[i][y] ==  0 ) return 1;
        }
	}
	for (int i = y-1; i <= y+1; i+=2){
        if ((i >= 0) && (i < size_y)){
            if ( array[x][i] ==  0 ) return 1;
        }
	}
	return 0;
}

/******************************************************************************
 * a3()
 *
 * Arguments: array - table data structure
 *            x - x coordinate of target element of the table structure
 *            y - y coordinate of target element of the table structure
 *            size_x - max x coordinate of the table structure
 *            size_y - max y coordinate of the table structure
 * Returns: integer based on the value of nearby table elements
 * Side-Effects: none
 *
 * Description: Executes mode a3
 *****************************************************************************/
int a3(short **array,int x, int y,int size_x,int size_y){

	if( (x < 1) || (x > size_x) || (y > size_y) || (y < 1)) return -2;
    x--; y--;

	for (int i = x-1; i <= x+1; i+=2){
        if ((i >= 0) && (i < size_x)){
            if ( array[i][y] > 0 ) return 1;
        }
	}
	for (int i = y-1; i <= y+1; i+=2){
        if ((i >= 0) && (i < size_y)){
            if ( array[x][i] > 0 ) return 1;
        }
	}
	return 0;
}

/******************************************************************************
 * a4()
 *
 * Arguments: array - table data structure
 *            x - x coordinate of target element of the table structure
 *            y - y coordinate of target element of the table structure
 *            size_x - max x coordinate of the table structure
 *            size_y - max y coordinate of the table structure
 * Returns: integer based on the value of nearby table elements
 * Side-Effects: none
 *
 * Description: Executes mode a4
 *****************************************************************************/
int a4(short **array,int x, int y,int size_x,int size_y){

	if( (x < 1) || (x > size_x) || (y > size_y) || (y < 1)) return -2;
    x--; y--;

	for (int i = x-1; i <= x+1; i+=2){
        if ((i >= 0) && (i < size_x)){
            if ( array[i][y] == -1 ) return 1;
        }
	}
	for (int i = y-1; i <= y+1; i+=2){
        if ((i >= 0) && (i < size_y)){
            if ( array[x][i] == -1 ) return 1;
        }
	}
	return 0;	
}
/******************************************************************************
 * a5()
 *
 * Arguments: array - table data structure
 *            x - x coordinate of target element of the table structure
 *            y - y coordinate of target element of the table structure
 *            size_x - max x coordinate of the table structure
 *            size_y - max y coordinate of the table structure
 * Returns: integer based on if the element from the table is breakable or not
 * Side-Effects: none
 *
 * Description: Executes mode a5
 *****************************************************************************/
int a5(short **array,int x, int y,int size_x,int size_y){
    int count = 0;
    if( (x < 1) || (x > size_x) || (y > size_y) || (y < 1)) return -2;

    x--; y--;

    if(array[x][y] <= 0) return -1;

    if(   ((x == 0) && (y == 0) )|| ( (x == 0) && ((y+1)==size_y) ) || ( ((y+1)==size_y) && ((x+1)==size_x) ) || ( (y == 0) && ((x+1) == size_x) )    ) return 0;

    if( y == 0){
        if( (array[x-1][y] == 0) && (array[x+1][y] == 0)) return 1;
        return 0;
    }
    if( (y+1) == size_y){
        if( (array[x-1][y] == 0) && (array[x+1][y] == 0)) return 1;
        return 0;
    }

    if( x == 0){
        if( (array[x][y-1] == 0) && (array[x][y+1] == 0)) return 1;
        return 0;
    }

    if( (x+1) == size_x){
        if( (array[x][y-1] == 0) && (array[x][y+1] == 0)) return 1;
        return 0;
    }
        
    if(array[x-1][y] != 0) count++;
    if(array[x][y+1] != 0) count++;
    if(array[x+1][y] != 0) count++;
    if(array[x][y-1] != 0) count++;
    
    if(count>2) return 0;
    if(count <= 1) return 1;
    
    if(count == 2){
        if( (array[x-1][y] != 0 && array[x+1][y] != 0) || (array[x][y-1] != 0 && array[x][y+1] != 0) )return 1;
    }
        
    return 0;
}
/******************************************************************************
 * a6()
 *
 * Arguments: array - table data structure
 *            x1 - x coordinate of target element of the table structure
 *            y1 - y coordinate of target element of the table structure
 *            x2 - x coordinate of second target element of the table structure
 *            y2 - y coordinate of second target element of the table structure
 *            limX - max x coordinate of the table structure
 *            limY - max y coordinate of the table structure
 * Returns: 1 if both elements are in the same room, else returns 0
 * Side-Effects: Deals poorly with "spirals" and "u-turns"
 *
 * Description: Executes mode a6. Virus type function, where one cell is
 *              "infected" and infects other nearby ones
 *****************************************************************************/
int a6(short **array,int x1, int y1,int x2,int y2, int limX, int limY){
    int flag = 1;

    if( x1 < 1 || x1 > limX || y1 > limY || y1 < 1 ||  x2 < 1 || x2 > limX || y2 > limY || y2 < 1) return -2;
    x1--; x2--; y1--; y2--;

    if(array[x2][y2] != 0 || array[x1][y1] != 0) return 0;
    
    array[x1][y1] = -8;

    for(int i = 0; (i < MAX_I) && (flag == 1); i++){
        flag = 0;
        for(int x = x1-i; x <= x1+i; x++){
            for(int y = y1-i; y <= y1+i; y++){
                if((x>=0) && (y>=0) && (x < limX) && (y < limY)){
                    if(array[x2][y2] == -8) return 1;
                        if (array[x][y] == -8){
                            if ((x+1 >= 0) && (x+1 < limX) && (y >= 0) && (y < limY)){
                                if (array[x+1][y] == 0){
                                    array[x+1][y] = -8;
                                    flag = 1;
                                }
                                array[x][y] = -7;
                            }
                            if ((x-1 >= 0) && (x-1 < limX) && (y >= 0) && (y < limY)){
                                if (array[x-1][y] == 0){
                                    array[x-1][y] = -8;
                                    flag = 1;  
                                }
                                array[x][y] = -7;          
                            }
                            if ((x >= 0) && (x < limX) && (y-1 >= 0) && (y-1 < limY)){
                                if (array[x][y-1] == 0){
                                    array[x][y-1] = -8;
                                    flag = 1;
                                }
                                array[x][y] = -7;
                            }
                            if ((x >= 0) && (x < limX) && (y+1 >= 0) && (y+1 < limY)){
                                if (array[x][y+1] == 0){
                                    array[x][y+1] = -8;
                                    flag = 1;
                                }
                                array[x][y] = -7;
                            }
                        }
                }  
            }
        }
    }
    if (array[x2][y2] == -7 || array[x2][y2] == -8) return 1;
    else return 0;
}
