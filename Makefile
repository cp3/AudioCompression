audoCompression.o: audioCompression.c
	gcc -Wall audioCompression.c -o audioCompression.o
run:
	./audioCompression.o
clean:
	rm -f audioCompression.o
assembly:
	arm-gcc -S audioCompression.c
