GCC = gcc -g -Werror -Wall -Wshadow -O3 -lm
OBJS = main.o path.o
OBJS2 = test.o path.o
MEM = valgrind --tool=memcheck --leak-check=full --show-reachable=yes -v

pa04: $(OBJS) path.h
	$(GCC) $(OBJS) path.h -o pa04

.c.o:
	$(GCC) -c $*.c

test: pa04
	./pa04 PA4_examples/map5x5.txt PA4_examples/query5x5.txt
	#./pa04 PA4_examples/usa.txt PA4_examples/usa10.txt

memory: pa04
	 $(MEM) ./pa04 PA4_examples/map5x5.txt query5x5.txt

some: $(OBJS2) path.h 
	$(GCC) $(OBJS2) path.h -o some

jordan: some
	./some PA4_examples/query5x5.txt

clean:
	/bin/rm -f *.o
