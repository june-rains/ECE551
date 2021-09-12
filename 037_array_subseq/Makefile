CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall

myProgram: test-subseq.o maxSeq.o
	gcc -o myProgram test-subseq.o maxSeq.o

%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean depend
clean:
	rm -f myProgram *.o *.c~ *.h~
depend:
	makedepend $(SRCS)
