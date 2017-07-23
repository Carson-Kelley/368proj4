#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct edge
{
	int l;	//Corresponds to the label of the left of edge as shown in file
	int r;	//Corresponds to the label of the right of edge as shown in file
	int distance;	//The length of this edge

}edge;

typedef struct node
{
	int label;
	int x;
	int y;
	bool visited;

}node;

typedef struct graph
{
	node *nodes;	//Array of all the nodes
	edge *edges;	//Array of all the edges

}graph;

typedef struct queries
{
	int start;
	int finish;

}queries;

graph *Load_Graph(char *filename, graph *input);

queries *Load_Queries(char *filename);

void FreeQueries(queries * test);

void FreeGraph(graph *map);
