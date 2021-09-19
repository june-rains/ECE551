CFLAGS = -std=gnu99 -Wall -Werror -pedantic 
test: test.o
	gcc -o test test.o
%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean depend
clean:
	rm -f test *.o *.c~ *.h~
depend:
	makedepend $(SRCS)
