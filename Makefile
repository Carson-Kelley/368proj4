GCC = gcc -g -Werror -Wall -Wshadow -O3
OBJS = main.o path.o
OBJS2 = test.o path.o
MEM = valgrind --tool=memcheck --leak-check=full --show-reachable=yes -v

pa04: $(OBJS) path.h
	$(GCC) $(OBJS) path.h -o pa04 -lm

.c.o:
	$(GCC) -c $*.c

test: pa04
	./pa04 PA4_examples/map5x5.txt PA4_examples/query5x5.txt
	./pa04 PA4_examples/usa.txt PA4_examples/usa1.txt
	./pa04 PA4_examples/map6.txt PA4_examples/query2.txt
	./pa04 PA4_examples/usa.txt PA4_examples/usa10.txt
	./pa04 PA4_examples/usa.txt PA4_examples/usa100.txt

memory: pa04
	 $(MEM) ./pa04 PA4_examples/map5x5.txt PA4_examples/query5x5.txt

instmem: PA4_examples/shortestpath
	$(MEM) ./PA4_examples/shortestpath PA4_examples/usa.txt PA4_examples/usa1.txt

inst: PA4_examples/shortestpath
	./PA4_examples/shortestpath PA4_examples/map5x5.txt PA4_examples/query5x5.txt
	./PA4_examples/shortestpath PA4_examples/usa.txt PA4_examples/usa1.txt
	./PA4_examples/shortestpath PA4_examples/usa.txt PA4_examples/usa10.txt
	./PA4_examples/shortestpath PA4_examples/usa.txt PA4_examples/usa100.txt

some: $(OBJS2) path.h 
	$(GCC) $(OBJS2) path.h -o some

jordan: some
	./some PA4_examples/query5x5.txt

clean:
	/bin/rm -f *.o
