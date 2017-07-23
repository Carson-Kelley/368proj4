graph *Load_Graph(char *filename, graph *input)
{
	return input;
}
queries *Load_Queries(char *filename){
	FILE * in = fopen(filename, "-r");

	int size;

	fscanf("%d", size);

	queries * input = malloc(sizeof(queries) * (size+1));

	for(int i = 0; i < size; i++){
	}

	return input;
}

