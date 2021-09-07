CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall

myProgram: test-power.o power.o
	gcc -o myProgram test-power.o power.o

%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean depend
clean:
	rm -f myProgram *.o *.c~ *.h~
depend:
	makedepend $(SRCS)
