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
	int i = 0;
	for(i = 0; (i< map->vertices); i = i + 1){
		while(map->nodes[i].head != NULL){
			edge * freeE = map->nodes[i].head;
			map->nodes[i].head = map->nodes[i].head->next;
			free(freeE);	
		}
	}
	free(map->nodes);
	free(map);	
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
	edge *curr = head;

	while(curr->next != NULL && (curr->next->distance < new->distance))
	{
		curr = curr->next;
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

	if(fscanf(in, "%d %d\n", &vertices, &edges) != 2)
	return NULL;
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
	int l = 0;
	int r = 0;
	edge *curr = NULL;
	int distance = 0;

	i = 0;
	while(i < edges)
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

		curr = malloc(sizeof(edge));
		curr->dest = l;
		curr->distance = distance;
		curr->next = NULL;
		input->nodes[r].head = Insert_Edge(input->nodes[r].head, curr);
		i++;
		fseek(in, 1, SEEK_CUR);
	}
	
	/*
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
	*/

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

void printqueue(nodeList *list)
{
	while(list != NULL)
	{
		printf("%d ", list->data->label);
		list = list->next;
	}
}

nodeList *push(nodeList *head, node *new)
{
	nodeList *newList= malloc(sizeof(nodeList));
	newList->data = new;
	newList->next = NULL;
	nodeList *curr = head;
	if(head == NULL || head->data->weight >= newList->data->weight)
	{
		newList->next = head;
		head = newList;
		return head;
	}
	while(curr->next != NULL && curr->next->data->weight < newList->data->weight)
	{
		curr = curr->next;
	}
	newList->next = curr->next;
	curr->next = newList;

	return head;
}

nodeList *pop(nodeList **head)
{
	nodeList *temp;
	temp = *head;
	*head = (*head)->next;
	return temp;
}

//Function will reorder a node in the queue after its weight has been changed
nodeList *reorder(nodeList *head, node *target)
{
	if(head == NULL || head->next == NULL)
	{
		return head;
	}
	nodeList *curr = head;
	nodeList *remove = NULL;
	if(head->data == target)
	{
		remove = head;
		head = head->next;
		remove->next = NULL;
		head = push(head, remove->data);
		free(remove);
		return head;
	}

	while(/*curr->next != NULL &&*/ curr->next->data != target)
	{
		curr = curr->next;
	}
	remove = curr->next;
	curr->next = remove->next;
	remove->next = NULL;
	head = push(head, remove->data);
	free(remove);
	return head;
	
}

void freeList(nodeList *head)
{
	if(head->next != NULL)
	{
		freeList(head->next);
	}
	free(head);
}

void dijkstras(graph *map, int start, int end)
{

	if((start > map->vertices - 1) || (start > map->vertices - 1) || start < 0 || end < 0)
	{
		printf("INF\n%d %d\n", start, end);
		return;
	}
	nodeList *head = NULL;
	nodeList *currList = NULL;
	node *curr = NULL;
	edge *currEdge = NULL;
	int distance = 0;
	//nodeList *visited = NULL;
	int i = 0;
	for(i = 0; i < map->vertices; i++)
	{
		if(i == start)
		{
			map->nodes[i].weight = 0;
		}
		else
		{
			map->nodes[i].weight = INT_MAX;
		}
		map->nodes[i].prev = NULL;
		map->nodes[i].visited = false;
		head = push(head, &(map->nodes[i]));
	}

/*	nodeList *print = head;
	printqueue(print);*/

	while(head != NULL)
	{
		currList = pop(&head);
		curr = currList->data;
		if(curr->label == end)
		{
			if(curr->weight == INT_MAX)
			{
				freeList(head);
				printf("INF\n%d %d\n", start, end);
				return;
			}
			printf("%d\n", curr->weight);
			printlist(curr);
			printf("\n");
			freeList(head);
			return;
		}
		currEdge = curr->head;
		while(currEdge != NULL)
		{
			distance = curr->weight + currEdge->distance;
			if(distance < map->nodes[currEdge->dest].weight)
			{
				map->nodes[currEdge->dest].weight = distance;
				map->nodes[currEdge->dest].prev = curr;
				head = reorder(head, &(map->nodes[currEdge->dest]));
			}
			currEdge = currEdge->next;
		}
		free(currList);
	}

	if(curr->weight == INT_MAX)
	{
		freeList(head);
		printf("INF\n%d %d\n", start, end);
		return;
	}
	freeList(head);
	printf("%d\n", curr->weight);
	printlist(curr);
	printf("\n");
	return;

}
