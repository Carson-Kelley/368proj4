#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "path.h"

void FreeQueries(queries *test)
{
	
}

void FreeGraph(graph *map)
{
	
}

graph *Load_Graph(char *filename, graph *input)
{
	int vertices;
	int edges;
	FILE *in = fopen(filename, "r");

	fscanf(in, "%d %d\n", &vertices, &edges);
	input->nodes = malloc(sizeof(node) * (vertices + 1));
	input->edges = malloc(sizeof(edge) * (edges + 1));
	//(input->nodes)[vertices] = NULL;
	//&(input->edges)[edges] = NULL;
	int i = 0;
	while(i < vertices)
	{
		fscanf(in, "%d %d %d\n", &(input->nodes[i].label), &(input->nodes[i].x), &(input->nodes[i].y);
		i++;
	}
	fscanf(in, "", &(graph->));

	fclose(in);
	return input;
}
queries * Load_Queries(char *filename){
	FILE * in = fopen(filename, "-r");

	int size;
	int i;

	fscanf("%d\n", &size);

	queries * input = malloc(sizeof(queries) * (size+1));

	for(i = 0; i < size; i++){
		fscanf("%d %d\n"&input[i]->start, &input[i]->finish);
	}

	input[i] = NULL;
	fclose(input);
	return input;
}

