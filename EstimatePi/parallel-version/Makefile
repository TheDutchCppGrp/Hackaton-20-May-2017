# Use Intel CPP compiler 
CC = icpc

CXXFLAGS = -std=c++11 

CXXFLAGS += -O2 -ltbb -I"/usr/local/include/"

LDFLAGS = -L/opt/intel/lib -L/opt/intel/lib/intel64 -L/opt/intel/tbb/lib -L/opt/intel/mkl/lib
 
SimplePiCalculationParallel: main.o
	$(CC) $(CXXFLAGS) -o SimplePiCalculationParallel main.o $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp

clean: 
	rm -rf *.o SimplePiCalculationParallel

