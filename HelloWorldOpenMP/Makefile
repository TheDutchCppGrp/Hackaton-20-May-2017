# Use Intel CPP compiler 
CC = icpc

CXXFLAGS = -qopenmp -O0

LDFLAGS = 
 
hello_v1: hello_v1.o
	$(CC) $(CXXFLAGS) -o hello_v1 hello_v1.o $(LDFLAGS)

hello_v1.o: hello_v1.cpp
	$(CC) $(CXXFLAGS) -c hello_v1.cpp

clean: 
	rm -rf *.o hello_v1

