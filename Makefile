all: mytests

mytests: mytests.o HashMap.o HashMapTree.o Set.o
	g++ -o mytests HashMap.o HashMapTree.o Set.o mytests.o 
	./mytests

mytests.o: mytests.cpp
	g++ -c mytests.cpp

HashMap.o: HashMap.cpp HashMap.hpp
	g++ -c HashMap.cpp

HashMapTree.o: HashMapTree.cpp HashMapTree.hpp
	g++ -c HashMapTree.cpp

Set.o: Set.cpp Set.hpp
	g++ -c Set.cpp

clean:
	rm *.o mytests
	clear

