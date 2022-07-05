output: tproc.o
	gcc tproc.o -o output

tproc.o: tproc.c
	gcc -c tproc.c

clean: 
	rm *.o output