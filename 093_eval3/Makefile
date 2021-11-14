cyoa-step3: cyoa-step3.o cyoa3.o
	g++ -o cyoa-step3 -ggdb3 cyoa-step3.o cyoa3.o
cyoa-step2: cyoa-step2.o cyoa2.o
	g++ -o cyoa-step2 -ggdb3 cyoa-step2.o cyoa2.o
cyoa-step1: cyoa-step1.o cyoa.o
	g++ -o cyoa-step1 -ggdb3 cyoa-step1.o cyoa.o
cyoa.o: cyoa.cpp cyoa.hpp
	g++ -std=gnu++98 -pedantic -Wall -Werror -ggdb3 -c cyoa.cpp
cyoa2.o: cyoa2.cpp cyoa2.hpp
	g++ -std=gnu++98 -pedantic -Wall -Werror -ggdb3 -c cyoa2.cpp
cyoa3.o: cyoa3.cpp cyoa3.hpp
	g++ -std=gnu++98 -pedantic -Wall -Werror -ggdb3 -c cyoa3.cpp
cyoa-step1.o:cyoa.cpp cyoa.hpp cyoa-step1.cpp
	g++ -std=gnu++98 -pedantic -Wall -Werror -ggdb3 -c cyoa-step1.cpp
cyoa-step2.o:cyoa2.cpp cyoa2.hpp cyoa-step2.cpp
	g++ -std=gnu++98 -pedantic -Wall -Werror -ggdb3 -c cyoa-step2.cpp
cyoa-step3.o:cyoa3.cpp cyoa3.hpp cyoa-step3.cpp
	g++ -std=gnu++98 -pedantic -Wall -Werror -ggdb3 -c cyoa-step3.cpp

clean:
	rm -f *~ *.o cyoa-step1 cyoa-step2 cyoa-step3 
