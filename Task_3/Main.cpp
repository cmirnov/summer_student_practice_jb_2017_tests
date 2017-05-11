#include "Solver.h"


int main(int argc, char *argv[]) {
  try {
    Input* input = new Input(argc, argv);
    if (!strcmp(argv[1], "--help")) {
      return 0;
    }
    Solver* solver = new Solver(input);
    solver->run();
    return 0;
  }
  catch(InvalidOption *e) {
    e->showMessage();
  }
  catch(InvalidNumberOfArg *e) {
    e->showMessage();
  } 
  return 0;
}
