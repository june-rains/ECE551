cyoa-step1: cyoa-step1.o cyoa.o
	g++ -o cyoa-step1 -ggdb3 cyoa-step1.o cyoa.o
cyoa.o: cyoa.cpp cyoa.hpp
	g++ -std=gnu++98 -pedantic -Wall -Werror -ggdb3 -c cyoa.cpp
cyoa-step1.o:cyoa.cpp cyoa.hpp cyoa-step1.cpp
	g++ -std=gnu++98 -pedantic -Wall -Werror -ggdb3 -c cyoa-step1.cpp
clean:
	rm -f *~ *.o cyoa-step1
