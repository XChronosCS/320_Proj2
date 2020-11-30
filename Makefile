M = cache-sim
R = DirectMap
S = SetAssoc
F = FullAssoc
CFLAGS= -g -Wall -Ofast -Werror -std=c++14

all: $(M)

$(M): $(M).o $(R).o $(S).o $(F).o
	g++ $(CFLAGS) $(M).o $(R).o $(S).o $(F).o -o $(M)

$(M).o: $(M).cpp
	g++ $(CFLAGS) -c $(M).cpp -o $(M).o
$(R).o: $(R).cpp
	g++ $(CFLAGS) -c $(R).cpp -o $(R).o
$(S).o: $(S).cpp
	g++ $(CFLAGS) -c $(S).cpp -o $(S).o
$(F).o: $(F).cpp
	g++ $(CFLAGS) -c $(F).cpp -o $(F).o


.PHONY: clean all memcheck

clean:
	rm -rf *.o $(M).o $(M) 

memcheck: $(M)
	valgrind --leak-check=full ./$(M)
