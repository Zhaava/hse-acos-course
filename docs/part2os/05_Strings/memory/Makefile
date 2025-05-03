all: malloc test

malloc:
	gcc -Wall -shared -fpic -o libmalloc.so malloc.c -ldl
test:
	gcc test.c -o test
run:
	LD_PRELOAD="./libmalloc.so" ./test
debug:
	gdb -iex "set exec-wrapper env LD_PRELOAD=./libmalloc.so" ./test
clean:
	rm -f test *.so *.o
