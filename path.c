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

int Find_Dist(node a, node b){
	double sum;
	int x = (a.x)-(b.x);
	int y = (a.y)-(b.y);
	sum = pow(x, 2) - pow(y,2);	
	int dist = (int) (sqrt(sum));

	return dist;

}

graph *Load_Graph(char *filename, graph *input)
{
	int vertices;
	int edges;
	FILE *in = fopen(filename, "r");

	fscanf(in, "%d %d\n", &vertices, &edges);
	input->nodes = malloc(sizeof(node) * (vertices));
	input->vertices = vertices;
	int i = 0;
	while(i < vertices)
	{
		fscanf(in, "%d %d %d\n", &(input->nodes[i].label), &(input->nodes[i].x), &(input->nodes[i].y));
		//printf("%d %d %d\n", input->nodes[i].label, input->nodes[i].x, input->nodes[i].y);
		input->nodes[i].head = NULL;
		i++;
	}
	char c = 'a';
	int l = 0;
	int r = 0;
	i = 0;
	edge *curr = NULL;
	int distance = 0;

	do
	{
		fscanf(in, "%d %d", &l, &r);
		//printf("%d %d\n", l, r);
		//Calculate the distance below
		curr = malloc(sizeof(edge));
		curr->dest = r;
		distance = Find_Dist(input->nodes[l], input->nodes[r]);
		curr->distance = distance;
		//curr->distance = l;
		curr->next = input->nodes[l].head;
		input->nodes[l].head = curr;

		curr = malloc(sizeof(edge));
		curr->dest = l;
		curr->distance = distance;
		curr->next = input->nodes[r].head;
		input->nodes[r].head = curr;
		
		//input->edges[i].distance = pow(xdiff + ydiff, 0.5);
		//printf("Distance: %d\n", input->edges[i].distance);
	}while((c = fgetc(in)) != EOF);

	/*
	i = 0;
	while(i < input->vertices)
	{
		curr = input->nodes[i].head;
		while(curr != NULL)
		{
			printf("%d\n", curr->dest);
			curr = curr->next;
		}
		i++;
		printf("\n");
	}*/

	

	fclose(in);
	return input;
}

queries * Load_Queries(char *filename, int * size){
	FILE * in = fopen(filename, "r");

	int i;

	fscanf(in,"%d\n", size);

	queries * input = malloc(sizeof(queries) * (*size));

	for(i = 0; i < (*size); i++){
		fscanf(in,"%d %d\n",&(input[i].start), &(input[i].finish));
	}

	//input[i] = NULL;
	fclose(in);
	return input;
}

void dijkstras(graph * map, int start, int end){





}
