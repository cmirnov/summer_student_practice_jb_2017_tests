Main: Main.o Input.o Solver.o InvalidNumberOfArg.o InvalidOption.o Support.o
	g++ -std=c++11 Main.cpp Input.cpp Solver.cpp InvalidNumberOfArg.cpp InvalidOption.cpp Support.cpp -o Main -lstdc++fs -pthread
Main.o: Main.cpp Solver.h
	g++ -c -std=c++11 Main.cpp -lstdc++fs -pthread
Solver.o: Solver.cpp Solver.h Input.h
	g++ -c -std=c++11 Solver.cpp -lstdc++fs -pthread
Input.o: Input.cpp Input.h InvalidNumberOfArg.h InvalidOption.h
	g++ -c -std=c++11 Input.cpp -lstdc++fs -pthread
InvalidNumberOfArg.o: InvalidNumberOfArg.cpp InvalidNumberOfArg.h
	g++ -c -std=c++11 InvalidNumberOfArg.cpp -lstdc++fs -pthread
InvalidOption.o: InvalidOption.cpp InvalidOption.h
	g++ -c -std=c++11 InvalidOption.cpp -lstdc++fs -pthread
Support.o: Support.cpp Support.h
	g++ -c -std=c++11 Support.cpp -lstdc++fs -pthread
