CC=g++
CFLAGS=-Wall -Wextra -std=c++17 -g

TARGETS=walsh statistics prinel

build:	$(TARGETS)

walsh:	walsh.cpp
	$(CC) $(CFLAGS) walsh.cpp -o walsh
	
statistics:	statistics.cpp
	$(CC) $(CFLAGS) statistics.cpp -o statistics
	
prinel:	prinel.cpp
	$(CC) $(CFLAGS) prinel.cpp -o prinel

run-p1:
	./walsh

run-p2:      
	./statistics
	
run-p3:
	./prinel

run-p4:      # nume necesar

clean:
	rm -f $(TARGETS)
