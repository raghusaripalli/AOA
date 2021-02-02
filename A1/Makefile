CC = g++ -O2 -Wall "-Wl,--stack=1073741824" -Wno-deprecated

all: simulated_test

simulated_test: graph_operations.o simulated_test.o 
				$(CC) -o simulated_test graph_operations.o simulated_test.o

graph_operations.o: graph_operations.cc 
					$(CC) -g -c graph_operations.cc

simulated_test.o: simulated_test.cc 
					$(CC) -g -c simulated_test.cc

clean: 
	rm -f *.o
	rm -f *.exe

clean_win:
	del *.o
	del *.exe