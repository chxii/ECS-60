netdriver.out: maxfinder.o NetDriver.o QuadraticProbing.o
	g++ -Wall -ansi -g -o netdriver.out maxfinder.o NetDriver.o QuadraticProbing.o


maxfinder.o: maxfinder.cpp NetDriver.h maxfinder.h QuadraticProbing.h   
	g++ -Wall -ansi -g -c maxfinder.cpp

NetDriver.o: NetDriver.cpp CPUTimer.h NetDriver.h maxfinder.h 
	g++ -Wall -ansi -g -c NetDriver.cpp

QuadraticProbing.o: QuadraticProbing.cpp QuadraticProbing.h
	g++ -Wall -ansi -g -c QuadraticProbing.cpp

clean:
	rm -f netdriver.out maxfinder.o NetDriver.o QuadraticProbing.o
