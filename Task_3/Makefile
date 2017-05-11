Main: Main.o Input.o Solver.o InvalidNumberOfArg.o InvalidOption.o
	g++ -std=c++11 Main.cpp Input.cpp Solver.cpp InvalidNumberOfArg.cpp InvalidOption.cpp -o Main -lstdc++fs
Main.o: Main.cpp Solver.h
	g++ -c -std=c++11 Main.cpp -lstdc++fs
Solver.o: Solver.cpp Solver.h Input.h
	g++ -c -std=c++11 Solver.cpp -lstdc++fs
Input.o: Input.cpp Input.h InvalidNumberOfArg.h InvalidOption.h
	g++ -c -std=c++11 Input.cpp -lstdc++fs
InvalidNumberOfArg.o: InvalidNumberOfArg.cpp InvalidNumberOfArg.h
	g++ -c -std=c++11 InvalidNumberOfArg.cpp -lstdc++fs
InvalidOption.o: InvalidOption.cpp InvalidOption.h
	g++ -c -std=c++11 InvalidOption.cpp -lstdc++fs
