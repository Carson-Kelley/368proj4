#include <stdio.h>
#include <stdlib.h>
#include <path.h>

int main(int argc, char **argv)
{

	graph *map = malloc(sizeof(graph));
	map = Load_Graph(argv[1], map);

	queries *tests = Load_Queries(argv[2]);
	return EXIT_SUCCESS;
}
