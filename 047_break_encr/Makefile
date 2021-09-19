CFLAGS = -std=gnu99 -Wall -Werror -pedantic -ggdb3 
breaker: breaker.o
	gcc -o  breaker breaker.o
%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean depend
clean:
	rm -f test *.o *.c~ *.h~
depend:
	makedepend $(SRCS)

