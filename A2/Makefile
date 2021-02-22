CC = g++ -O2 -Wall

all: simulated_test 

simulated_test: skyline.o simulated_test.o
				$(CC) -o simulated_test skyline.o simulated_test.o


skyline.o: skyline.cc
				$(CC) -g -c skyline.cc

simulated_test.o: simulated_test.cc 
					$(CC) -g -c simulated_test.cc

clean: 
	rm -f *.o
	rm -f *.exe

clean_win:
	del -f *.o
	del -f *.exe