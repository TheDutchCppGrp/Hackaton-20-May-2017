# Use Intel CPP compiler 
CC = icpc

CXXFLAGS = -std=c++14 
CXXFLAGS += -I"/usr/local/include/" 
CXXFLAGS += $(EXTRA_CXXFLAGS)

SimplePiCalculation: main.o
	$(CC) $(CXXFLAGS) -o SimplePiCalculation main.o

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp

clean: 
	rm -rf *.o SimplePiCalculation

