#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "path.h"

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		return EXIT_FAILURE;
	}
	graph *map = malloc(sizeof(graph));
	map = Load_Graph(argv[1], map);

	/*queries *test;
	queries *tests = Load_Queries(argv[2], &test);

	FreeQueries(tests);*/
	FreeGraph(map);

	return EXIT_SUCCESS;
}
