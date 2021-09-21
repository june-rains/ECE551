CFLAGS = -std=gnu99 -Wall -Werror -pedantic -ggdb3 
rotateMatrix: rotateMatrix.o
	gcc -o  rotateMatrix rotateMatrix.o
%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean depend
clean:
	rm -f test *.o *.c~ *.h~
depend:
	makedepend $(SRCS)
