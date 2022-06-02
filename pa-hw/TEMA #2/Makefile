CC=g++
CFLAGS=-Wall -Wextra -std=c++17 -g

TARGETS=fortificatii curse beamdrone

build:	$(TARGETS)

fortificatii:	fortificatii.cpp
	$(CC) $(CFLAGS) fortificatii.cpp -o fortificatii

curse:	curse.cpp
	$(CC) $(CFLAGS) curse.cpp -o curse

beamdrone:	beamdrone.cpp
	$(CC) $(CFLAGS) beamdrone.cpp -o beamdrone	
	
run-p1:

run-p2:      
	./fortificatii
	
run-p3:
	./beamdrone
run-p4:
	./curse

clean:
	rm -f $(TARGETS)