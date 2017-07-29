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

	return dist;

}

edge *Insert_Edge(edge *head, edge *new)
{
	if(head == NULL || head->distance > new->distance)
	{
		new->next = head;
		head = new;
		return head;
	}
	//edge *prev = NULL;
	edge *curr = head;

	while(curr->next != NULL && (curr->next->distance < new->distance))
	{
		//prev = curr;
		curr = curr->next;
	}
	/*if(prev == NULL)
	{
		new->next = head;
		return new;
	}*/
	new->next = curr->next;
	curr->next = new;
	return head;
}

graph *Load_Graph(char *filename, graph *input)
{
	int vertices;
	int edges;
	FILE *in = fopen(filename, "r");

	if(fscanf(in, "%d %d\n", &vertices, &edges) != 2)
	return input;
	input->nodes = malloc(sizeof(node) * (vertices));
	input->vertices = vertices;
	int i = 0;
	while(i < vertices)
	{
		if(fscanf(in, "%d %d %d\n", &(input->nodes[i].label), &(input->nodes[i].x), &(input->nodes[i].y))!= 3){
			return input;
		}
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
		//printf("run: %d\n", i);
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

	if(fscanf(in,"%d\n", size) != 1)
		return NULL;

	queries * input = malloc(sizeof(queries) * (*size));

	for(i = 0; i < (*size); i++){
		if(fscanf(in,"%d %d\n",&(input[i].start), &(input[i].finish)) != 2){
			return NULL;
			}
	}

	//input[i] = NULL;
	fclose(in);
	return input;
}
void printlist(node *list){                                                                                                                                  
	if(list->prev != NULL){                                                                                                                               
		printlist(list->prev);                                                                                                                        
	}      
	printf("%d ",list->label);                                                                                                                                  
}

nodeList * Push(nodeList *head, nodeList *new)
{
	new->next = head;
	return new;
}

//This function will return the minimum weight node in the queue
nodeList * Pop(nodeList *head)
{
	nodeList *result = head;
	nodeList *curr = head->next;
	//nodeList *prev = head;
	nodeList *prev = head;
	while(curr != NULL)
	{
		if(curr->label->weight < result->label->weight)
		{
			result = curr;
			while(prev->next != curr)
			{
				/*if(prev == NULL)
				{
					prev = head;
				}
				else
				{*/
					prev = prev->next;
				//}
			}
		}
		curr = curr->next;
	}
	/*if(prev == curr)
	{
		result = head;
		head = head->next;
		return result;
	}*/
	prev->next = result->next;
	result->next = NULL;
	return result;
}

void dijkstras(graph * map, int start, int end){
	//int currIndex = start;
	//int nextIndex = 0;
	int distance = 0;
	int i = 0;
	node *curr;
	edge *currEdge = NULL;
	nodeList *head = NULL;
	nodeList *currList = head;
	
	//node *print = curr;
	
	for(i = 0; i < map->vertices; i++)
	{
		map->nodes[i].weight = INT_MAX;
		map->nodes[i].prev = NULL;
		map->nodes[i].visited = false;
		currList = malloc(sizeof(nodeList));
		currList->label = &(map->nodes[i]);
		head = Push(head, currList);
	}
	map->nodes[start].weight = 0;
	nodeList * temp;
	while(head != NULL)
	{

		currList = Pop(head);
		curr = currList->label;
		currEdge = curr->head;
		if(curr->label == end)
		{
			printf("%d\n", curr->weight);
			printlist(curr);
			printf("\n");
			while(currList != NULL){
				temp = currList;
				currList = currList->next;
				free(temp);
			}

			return;
		}
		while(currEdge != NULL)
		{
			distance = curr->weight + currEdge->distance;
			if (distance < map->nodes[currEdge->dest].weight)
			{
				map->nodes[currEdge->dest].weight = distance;
				map->nodes[currEdge->dest].prev = curr;
			}
			currEdge = currEdge->next;
			//Printing edges
			/*print = head;
			i = 0;
			while(i < map->vertices)
			{
				print = map->nodes[i].head;
				printf("Current node: %d\n", map->nodes[i].label);
				while(print != NULL)
				{
					printf("%d, %d\n", print->dest, print->distance);
					print = print->next;
				}
				i++;
				printf("\n");
			}*/

		}
		//free(currList);
	}
	printf("INF\n%d %d\n", start, end);



	return;

	//BEGINNING OF ALGORITHM THAT ALMOST WORKS
	/*
	while(map->nodes[end].visited != true)
	{
		printf("Current Index: %d\n", currIndex);
		currEdge = map->nodes[currIndex].head;
		//nextIndex = currEdge->dest;

		while((map->nodes[currEdge->dest].visited == true) && currEdge != NULL)
		{
			currEdge = currEdge->next;
			//nextIndex = currEdge->dest;
		}
		if(currEdge == NULL)
		{
			//curr
			printf("INF\n%d %d\n", start, end);
			return;
		}
		//nextIndex = (map->nodes[currIndex].head)->dest;
		currEdge = map->nodes[currIndex].head;
		while(currEdge != NULL)
		{
			//map->nodes[currEdge->dest].visited = true;
			distance = currEdge->distance + map->nodes[currIndex].weight;
			//map->nodes[currIndex].head = map->nodes[currIndex].head->next;
			if(distance < map->nodes[currEdge->dest].weight)
			{
				map->nodes[currEdge->dest].weight = distance;
				map->nodes[currEdge->dest].prev = &(map->nodes[currIndex]);
				Pop();
				Push();
			}
			currEdge = currEdge->next;
			currList = malloc(sizeof(nodeList));
			currList->list
				while()
				{

				}
		}
		map->nodes[currIndex].visited = true;
		//map->nodes[nextIndex].prev = &(map->nodes[currIndex]);
		currIndex = nextIndex;
		//free(currEdge);
	}
	*/
	//END OF ALGORITHM THAT ALMOST WORKS
	
	//Trying to fix final path
	/*currIndex = start;
	currEdge = map->nodes[currIndex].head;
	distance = 0;
	while(currIndex != end)
	{
		distance = map->nodes[currIndex].weight + currEdge;
		while(currEdge != NULL)
		{
			distance = map->nodes[currIndex].weight + currEdge;
		}
	}*/

	//printf("%d\n", map->nodes[currIndex].weight);
	//printlist(&(map->nodes[currIndex]));


}
