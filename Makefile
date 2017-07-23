GCC = gcc -g -Werror -Wall -Wshadow -O3
OBJS = packing_main.o packing.o
MEM = valgrind --tool=memcheck --leak-check=full --show-reachable=yes -v

pa03: $(OBJS) packing.h
	$(GCC) $(OBJS) packing.h -o pa03

.c.o:
	$(GCC) -c $*.c

test: pa03
	./pa03 input/r0_po.txt output/r0_out.txt
	diff input/r0.flr output/r0_out.txt
	./pa03 input/r6_po.txt output/r6_out.txt
	diff input/r6.flr output/r6_out.txt
	./pa03 input/r7_po.txt output/r7_out.txt

memory: pa03
	 $(MEM) ./pa03 input/r0_po.txt output/r0_out.txt
	 $(MEM) ./pa03 input/r6_po.txt output/r6_out.txt
	 $(MEM) ./pa03 input/r7_po.txt output/r7_out.txt

clean:
	/bin/rm -f *.o
