CXX=g++

PROJECT_O=Bmp.o Topograph.o

CXXFLAGS= -c -Wall -g -std=c++14

EXE=ImageEditor

default : main.o $(PROJECT_O)
	$(CXX) main.o $(PROJECT_O) -o $(EXE)
main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp
Bmp.o : Bmp.cpp
		$(CXX) $(CXXFLAGS) Bmp.cpp
Topograph.o : Topograph.cpp
		$(CXX) $(CXXFLAGS) Topograph.cpp
clean:
	rm *.o $(EXE)
run:
	./$(EXE)
