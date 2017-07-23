#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "path.h"

graph *Load_Graph(char *filename, graph *input)
{
	fscanf("%d", size);
	return input;
}
queries *Load_Queries(char *filename){
	FILE * in = fopen(filename, "-r");

	int size;
	int i;

	fscanf("%d\n", size);

	queries * input = malloc(sizeof(queries) * (size+1));

	for(i = 0; i < size; i++){
		fscanf("%d %d\n"input[i]->start, input[i]->finish);
	}

	input[i] = NULL;

	return input;
}

