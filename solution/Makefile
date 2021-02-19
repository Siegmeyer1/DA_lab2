CXX = g++
CXXFLAGS = -O3 -std=c++14

all: solution

solution: solution.o my_string.o save_load.o patricia.o
	$(CXX) $(CXXFLAGS) solution.o my_string.o save_load.o patricia.o -o solution

solution.o: solution.cpp
	$(CXX) $(CXXFLAGS) -c solution.cpp

my_string.o: my_string.cpp
	$(CXX) $(CXXFLAGS) -c my_string.cpp

save_load.o: save_load.cpp
	$(CXX) $(CXXFLAGS) -c save_load.cpp

patricia.o: patricia.cpp
	$(CXX) $(CXXFLAGS) -c patricia.cpp

clean:
	rm -rf *.o solution
