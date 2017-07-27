#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
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
	sum = pow(x, 2) + pow(y,2);	
	int dist = (int) (sqrt(sum));

	//printf("%d\n %d   %d   %d    %d \n", dist, a.x, a.y,b.x, b.y);
	return dist;

}

edge *Insert_Edge(edge *head, edge *new)
{
	if(head == NULL)
	{
		return new;
	}
	edge *prev = NULL;
	edge *curr = head;

	while(curr != NULL && (curr->distance < new->distance))
	{
		prev = curr;
		curr = curr->next;
	}
	if(prev == NULL)
	{
		new->next = head;
		return new;
	}
	if(curr == NULL)
	{
		prev->next = new;
		new->next = NULL;
		return head;
	}
	new->next = curr->next;
	curr->next = new;
	return head;
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
		//		printf("%d %d %d\n", input->nodes[i].label, input->nodes[i].x, input->nodes[i].y);
		input->nodes[i].head = NULL;
		i++;
	}
	char c = 'a';
	int l = 0;
	int r = 0;
	edge *curr = NULL;
	int distance = 0;

	/*do
	  {*/
	i = 1;
	fseek(in, -1, SEEK_CUR);
	while((c = fgetc(in)) != EOF)
	{
		if(fscanf(in, "%d %d", &l, &r) != 2)
		{
			break;
		}
		curr = malloc(sizeof(edge));
		curr->dest = r;
		distance = Find_Dist(input->nodes[l], input->nodes[r]);
		curr->distance = distance;
		curr->next = NULL;
		input->nodes[l].head = Insert_Edge(input->nodes[l].head, curr);
		//input->nodes[l].head = curr;

		curr = malloc(sizeof(edge));
		curr->dest = l;
		curr->distance = distance;
		curr->next = NULL;
		input->nodes[r].head = Insert_Edge(input->nodes[r].head, curr);
		//input->nodes[r].head = curr;
		printf("run: %d\n", i);
		i++;
	}

	i = 0;
	while(i < input->vertices)
	{
		curr = input->nodes[i].head;
		printf("Current node: %d\n", input->nodes[i].label);
		while(curr != NULL)
		{
			printf("%d, %d\n", curr->dest, curr->distance);
			curr = curr->next;
		}
		i++;
		printf("\n");
	}

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
void printlist(node * list){                                                                                                                                  
	if(list->next != NULL){                                                                                                                               
               printlist(list->next);                                                                                                                        
	}      
	printf(list->label);                                                                                                                                  
}	                                                              
void dijkstras(graph * map, int start, int end){
	int currIndex = start;
	int nextIndex = 0;
	int distance = 0;
	edge *currEdge = NULL;
	for(int i = 0; i < map->vertices; i++)
	{
		map->nodes[i].weight = INT_MAX;
		map->nodes[i].prev = NULL;
		map->nodes[i].visited = false;
	}
	map->nodes[start].weight = 0;

	/*for(int i = 0; i < map->vertices; i++)
	  {
	  map->nodes[];*/

	while(map->nodes[end].visited != true)
	{
		nextIndex = (map->nodes[currIndex].head)->dest;
		while(map->nodes[currIndex].head != NULL)
		{
			currEdge = map->nodes[currIndex].head;
			map->nodes[currEdge->dest].visited = true;
			distance = currEdge->distance + map->nodes[currIndex].weight;
			map->nodes[currIndex].head = map->nodes[currIndex].head->next;
			if(distance < map->nodes[currEdge->dest].weight)
			{
				map->nodes[currEdge->dest].weight = distance;
				map->nodes[currEdge->dest].prev = &(map->nodes[currIndex]);
			}
			free(currEdge);
		}
		currIndex = nextIndex;
	}

	printf("%d", nodes[currIndex].weight);
	printlist(nodes[currentIndex]);


}
