#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "path.h"

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Wrong number of arguments");
		return EXIT_FAILURE;
	}
	graph *map = malloc(sizeof(graph));
	map = Load_Graph(argv[1], map);

    int size;
	queries *tests = Load_Queries(argv[2], &size);
	
	int start;
	int finish;
	int i;
	for(i = 0; i < size; i++){
		start = tests[i].start;
		finish = tests[i].finish;
		dijkstras(map, start, finish);
	}

	FreeQueries(tests);
	FreeGraph(map);

	return EXIT_SUCCESS;
}
