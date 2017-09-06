forktest : forktest.c
	gcc -o forktest forktest.c
clean:
	rm -f forktest
