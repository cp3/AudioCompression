audoCompression.o: audoCompression.c
	gcc -Wall audoCompression.c -o audioCompression.o
run:
	./audioCompression.o
clean:
	rm -f audioCompression.o
