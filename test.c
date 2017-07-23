#include<stdio.h>
#include<stdlib.h>
#include"path.h"
#include<stdbool.h>

int main(int argc, char** argv){
	queries * que = Load_Queries(argv[1]);
	printf("%d \n", que[0].start);
}
