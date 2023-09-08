out : sum2.o sum.o
	gcc -o out sum2.o sum.o

sum2.o:
	gcc -c sum2.c

sum.o:
	gcc -c sum.c

clean:
	rm -rf sum2.o sum.o out
