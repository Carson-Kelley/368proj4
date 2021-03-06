#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<limits.h>

typedef struct edge
{
	//int l;	//Corresponds to the label of the left of edge as shown in file
	//int r;	//Corresponds to the label of the right of edge as shown in file
	int dest;	//The node that the edge will end on
	int distance;	//The length of this edge
	struct edge *next;	//Pointer to next edge in list

}edge;

typedef struct node
{
	int label;
	int x;
	int y;
	int weight;	//The weight of the minimum path to this node
	struct node *prev;
	bool visited;
	edge *head;

}node;

typedef struct nodeList
{
	node *data;
	struct nodeList *next;
}nodeList;

typedef struct graph
{
	node *nodes;	//Array of all the nodes
	int vertices;	//Number of vertices in the graph
	//Each node should have a linked list that contains all of its neighbors i.e. the edges that it has instead of a seperate edges array

}graph;

typedef struct queries
{
	int start;
	int finish;

}queries;

/*typedef struct nodeList
{
	int index;
	nodeList *next;
}nodeList;*/

graph *Load_Graph(char *filename, graph *input);

queries *Load_Queries(char *filename, int * size);

void FreeQueries(queries * test);

void FreeGraph(graph *map);

void dijkstras(graph * map, int start, int end);
