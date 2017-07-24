#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
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
	//input->nodes[vertices] = NULL;
	//input->edges[edges] = NULL;
	int i = 0;
	while(i < vertices)
	{
		fscanf(in, "%d %d %d\n", &(input->nodes[i].label), &(input->nodes[i].x), &(input->nodes[i].y));
		printf("%d %d %d\n", input->nodes[i].label, input->nodes[i].x, input->nodes[i].y);
		i++;
	}
	char c = 'a';
	i = 0;
	do
	{
		fscanf(in, "%d %d", &(input->edges[i].l), &(input->edges[i].r));
		printf("%d %d\n", input->edges[i].l, input->edges[i].r);
		//Calculate the distance below
		int xdiff = input->nodes[input->edges[i].l].x - input->nodes[input->edges[i].r].x;
		int ydiff = input->nodes[input->edges[i].l].y - input->nodes[input->edges[i].r].y;
		xdiff = pow(xdiff, 2);
		ydiff = pow(ydiff, 2);
		
		input->edges[i].distance = pow(xdiff + ydiff, 0.5);
		printf("Distance: %d\n", input->edges[i].distance);
		i++;
	}while((c = fgetc(in)) != EOF);

	

	fclose(in);
	return input;
}
/*
queries * Load_Queries(char *filename){
	FILE * in = fopen(filename, "r");

	int size;
	int i;

	fscanf(in,"%d\n", &size);

	queries * input = malloc(sizeof(queries) * (size));

	for(i = 0; i < size; i++){
		fscanf(in,"%d %d\n",&(input[i].start), &(input[i].finish));
	}

	//input[i] = NULL;
	fclose(in);
	return input;
}
*/
